// vim: set noexpandtab tabstop=2:

#include <spliced_aln/WordHitsGroupUtil.hpp>
#include <spliced_aln/aln_global.hpp>
#include <nonspliced_aln/nonsplicedAln.hpp>
#include <queue>

using namespace std;

int cal_two_wordchunks_backsearch_area_diff_sum(const WordHitsChunkPtr head_chunk, const WordHitsChunkPtr tail_chunk, const SeqString query, const SeqSuffixArray& ref_SAIndex, int num_backSearch)
{
	int head_chunk_diff = 0;
	int tail_chunk_diff = 0;
	for(int i = 0; i < num_backSearch; ++i)
	{
		long head_chunk_queryEnd = head_chunk->end_pos_in_query - i;
		long head_chunk_refEnd = head_chunk->end_pos_in_ref - i;
		if(query[head_chunk_queryEnd] != ref_SAIndex.char_at(head_chunk_refEnd))
		{
			++head_chunk_diff;
		}

		long tail_chunk_refEnd = tail_chunk->start_pos_in_ref + i;
		long tail_chunk_queryEnd = tail_chunk->start_pos_in_query + i;
		if(query[tail_chunk_queryEnd] != ref_SAIndex.char_at(tail_chunk_refEnd))
		{
			++tail_chunk_diff;
		}
	}
	return head_chunk_diff + tail_chunk_diff;
}

int locate_bridge_within_two_chunks_denovo(WordHitsChunkPtr& head_chunk, WordHitsChunkPtr& tail_chunk, std::list<WordHitsChunkBridgePtr>& wordhitschunkbridges, int num_backSearch, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
	WordHitsChunkBridgePtr bridge_to_be_added;
	int num_bridge_created = 0;

	int max_num_gapMM_increased_allowed = opt.local_wordChunk_diff;
	int best_num_gapMM_increased = max_num_gapMM_increased_allowed + 1;

	/*
	 * Assume num_backsearch = 2
	 *                                         head_chunk_ref_end_pos
	 *                                                 |
	 *                      search_area_ref_start_pos   |   max_bridge_ref_start_pos
	 * (head_chunk_ref_end_pos - num_backsearch)    \  |    /    (head_chunk_ref_end_pos + cleft_length + num_backsearch)
	 *                                               ↓ ↓   ↓
	 *                                      ref:  -----------------
	 *                               head_chunk → ||||||  |||||| ← tail_chunk
	 *                                    query:  ------..---------
	 *                                               ↑ ↑|| ↑
	 * (head_chunk_query_end_pos - num_backsearch)  / / ||  \    (head_chunk_query_end_pos + cleft_length + num_backsearch)
	 *                   min_bridge_query_start_pos  /  ||   max_bridge_query_end_pos
	 *                                              /   ||
	 *                      head_chunk_query_end_pos    ||
	 *                                             cleft_length
	 */

	int original_gapMM_sum = cal_two_wordchunks_backsearch_area_diff_sum(head_chunk, tail_chunk, query, ref_SAIndex, num_backSearch);
	long cleft_length = tail_chunk->start_pos_in_query - head_chunk->end_pos_in_query - 1;
	long min_bridge_ref_start_pos = head_chunk->end_pos_in_ref - num_backSearch;
	long max_bridge_ref_start_pos = head_chunk->end_pos_in_ref + cleft_length + num_backSearch;
	long min_bridge_query_start_pos = head_chunk->end_pos_in_query - num_backSearch;
	long max_bridge_query_end_pos = head_chunk->end_pos_in_query + cleft_length + num_backSearch + 1;
	SeqString search_query = query.get_infix(min_bridge_query_start_pos + 1, max_bridge_query_end_pos - 1);

	for(long curr_bridge_ref_start_pos = min_bridge_ref_start_pos
			, curr_bridge_ref_end_pos = tail_chunk->start_pos_in_ref - num_backSearch - cleft_length
			, curr_bridge_query_start_pos = min_bridge_query_start_pos
			; curr_bridge_ref_start_pos <= max_bridge_ref_start_pos
			; ++curr_bridge_ref_start_pos
			, ++curr_bridge_ref_end_pos
			, ++curr_bridge_query_start_pos)
	{
		if(curr_bridge_query_start_pos + 1 < opt.min_anchor_size || (query.get_length() - curr_bridge_query_start_pos - 1) < opt.min_anchor_size) continue;

		Strand::Value splice_strand = determin_strand_by_canonical_spliceSite(
				ref_SAIndex
				, curr_bridge_ref_start_pos + 1 // splice_site_donor_pos
				, curr_bridge_ref_end_pos - 1 //splice_site_acceptor_pos
				);

		if(splice_strand == Strand::none_decide) continue;
		//if((!(opt.strand_mode & Strand_mode::reverse)) && splice_strand != head_chunk->strand) continue; //Seems useless for now
		//if((!(opt.strand_mode & Strand_mode::forward)) && splice_strand == head_chunk->strand) continue;

		/*
		 * new_head_chunk_search_area: [min_bridge_ref_start_pos + 1, curr_bridge_ref_start_pos]
		 * new_tail_chunk_search_area: [curr_bridge_ref_end_pos, tail_chunk->start_pos_in_ref + num_backSearch - 1]
		 *
		 *                                               curr_bridge_ref_start_pos
		 *                      min_bridge_ref_start_pos        /  curr_bridge_ref_end_pos
		 *                                             \       /    |
		 *                                              \     /    /  tail_chunk->start_pos_in_ref + num_backSearch - 1
		 *                                               ||  |    |  |
		 *                                    ref:  =========.----.======
		 *                                         /      |  |    |  |   \
		 *                              head_chunk         \  \  /  /     tail_chunk
		 *                                                  |  ||  |
		 *                                   query: ===========..========
		 *                                                 ||      ||
		 *                                                /         |      
		 *                      min_bridge_query_start_pos   max_bridge_query_end_pos
		 *                                                           
		 *
		 */
		SeqString new_head_chunk_search_area = ref_SAIndex.get_infixSeq(min_bridge_ref_start_pos + 1, curr_bridge_ref_start_pos);
		SeqString new_tail_chunk_search_area = ref_SAIndex.get_infixSeq(curr_bridge_ref_end_pos, tail_chunk->start_pos_in_ref + num_backSearch - 1);

		GapAndMM search_area_gap_mm_with_bridge;
		aln_global(new_head_chunk_search_area + new_tail_chunk_search_area, search_query, search_area_gap_mm_with_bridge);
		int gapMM_sum_with_bridge = search_area_gap_mm_with_bridge.sum();
		int num_gapMM_increased = gapMM_sum_with_bridge - original_gapMM_sum;

		/*
		 *                                              search_area
		 *                                      ref: -------------------
		 *                  head_chunk_search_area → ||||||       |||||| ← tail_chunk_search_area
		 *               new_head_chunk_search_area→ ||||       |||||||| ← new_tail_chunk_search_area
		 *                                    query: -------...---------
		 *                                    
		 *            original_gapMM_sum = (head_chunk_search_area + tail_chunk_search_area) vs search_query
		 *            gapMM_sum_with_bridge = (new_head_chunk_search_area + new_tail_chunk_search_area) vs search_query
		 *                   num_gapMM_increased = gapMM_sum_with_bridge - original_gapMM_sum
		 */
		if(num_gapMM_increased < max_num_gapMM_increased_allowed)
		{
			WordHitsChunkBridgePtr new_bridge = make_shared<WordHitsChunkBridge>(
					head_chunk, tail_chunk
					, curr_bridge_ref_start_pos, curr_bridge_ref_end_pos
					, curr_bridge_query_start_pos, curr_bridge_query_start_pos + 1
					, splice_strand, search_area_gap_mm_with_bridge, original_gapMM_sum);
			head_chunk->is_first_in_bridge = false;
			tail_chunk->is_last_in_bridge = false;
			if(opt.report_best_only && num_gapMM_increased < best_num_gapMM_increased)
			{
				bridge_to_be_added = new_bridge;
				best_num_gapMM_increased = num_gapMM_increased;
			}
			else
			{
				wordhitschunkbridges.push_back(new_bridge);
				++num_bridge_created;
			}
		}
	}

	if(opt.report_best_only && bridge_to_be_added != nullptr)
	{
		wordhitschunkbridges.push_back(bridge_to_be_added);
		num_bridge_created = 1;
	}
	return num_bridge_created;
}

void collect_anchor_hits_within_bound(const SeqString& inner_chunk_and_ss, list<long>& anchor_hit_list, const SeqSuffixArray& ref_SAIndex, long hit_left_bound, long hit_right_bound, const alnNonspliceOpt& anchor_search_opt)
{
	std::queue<AlnResult> anchor_hit_result;
	nonsplicedAln(inner_chunk_and_ss, anchor_hit_result, ref_SAIndex, anchor_search_opt);
	while(!anchor_hit_result.empty())
	{
		AlnResult a = anchor_hit_result.front();
		anchor_hit_result.pop();
		for(unsigned long i = a.SA_index_low; i < a.SA_index_high; ++i)
		{
			long ref_hit_pos =  ref_SAIndex.SAIndex2SeqPos(i);
			if(ref_hit_pos >= hit_left_bound
					&& ((ref_hit_pos + inner_chunk_and_ss.get_length() - 1) <= hit_right_bound))
			{
				anchor_hit_list.push_back(ref_hit_pos);
			}
		}
	}
}

bool is_donor_splice_site(const SeqSuffixArray& ref, long ref_pos, bool revcomp)
{
	if(revcomp)
		return ref.char_at(ref_pos) == 'C' && ref.char_at(ref_pos + 1) == 'T';
	else
		return ref.char_at(ref_pos) == 'G' && ref.char_at(ref_pos + 1) == 'T';
}

bool is_acceptor_splice_site(const SeqSuffixArray& ref, long ref_pos, bool revcomp)
{
	if(revcomp)
		return ref.char_at(ref_pos) == 'A' && ref.char_at(ref_pos + 1) == 'C';
	else
		return ref.char_at(ref_pos) == 'A' && ref.char_at(ref_pos + 1) == 'G';
}

inline bool is_splice_site(const SeqSuffixArray& ref, long ref_pos, int splice_type, bool revcomp)
{
	if(splice_type == SpliceType::splice_donor)
		return is_donor_splice_site(ref, ref_pos, revcomp);
	else if(splice_type == SpliceType::splice_acceptor)
		return is_acceptor_splice_site(ref, ref_pos, revcomp);
	else
		return false;
}

Strand::Value determin_strand_by_canonical_spliceSite(const SeqSuffixArray& ref_SAIndex, long donor_pos, long acceptor_pos)
{
	if(is_donor_splice_site(ref_SAIndex, donor_pos, false) && is_acceptor_splice_site(ref_SAIndex, acceptor_pos - 1, false))
	{
		return Strand::forward;
	}
	if(is_donor_splice_site(ref_SAIndex, donor_pos, true) && is_acceptor_splice_site(ref_SAIndex, acceptor_pos - 1, true))
	{
		return Strand::reverse;
	}
	return Strand::none_decide;
}

bool is_splice_site_by_refPos(const SeqSuffixArray& ref, long ref_pos, SpliceType::Value splice_type, Strand::Value splice_strand)
{
	bool revcomp;
	if(splice_strand == Strand::forward)
		revcomp = false;
	else if(splice_strand == Strand::reverse)
		revcomp = true;
	else return false;

	if((splice_strand == Strand::forward && splice_type == SpliceType::splice_donor)
			|| (splice_strand == Strand::reverse && splice_type == SpliceType::splice_acceptor))
	{
		return is_splice_site(ref, ref_pos, splice_type, revcomp);
	}
	else
	{
		return is_splice_site(ref, ref_pos - 1, splice_type, revcomp);
	}
}

SeqString get_partner_splice_site(SpliceType::Value splice_type, Strand::Value splice_strand)
{
	if(splice_type == SpliceType::splice_donor)
	{
		if(splice_strand == Strand::forward)
			return SeqString("AG");
		else
			return SeqString("CT");
	}
	else
	{
		if(splice_strand == Strand::forward)
			return SeqString("GT");
		else
			return SeqString("AC");
	}
}

int locate_bridge_within_two_chunks_with_inner_exon_denovo(WordHitsChunkPtr& head_chunk, WordHitsChunkPtr& tail_chunk, std::list<WordHitsChunkBridgePtr>& wordhitschunkbridges, std::list<WordHitsChunkPtr>& wordhitschunks, int num_backSearch, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
	vector<int> head_chunk_search_area_mm;
	vector<int> tail_chunk_search_area_mm;
	cal_two_wordchunks_backsearch_area_mm(head_chunk, tail_chunk, head_chunk_search_area_mm, tail_chunk_search_area_mm, query, ref_SAIndex, num_backSearch);

	/*
	 * Assume num_backsearch = 2
	 *                                         head_chunk->end_pos_in_ref(max_head_bridge_ref_start_pos)
	 *                                                 |  tail_chunk->start_pos_in_ref(min_tail_bridge_ref_start_pos)
	 *                 min_head_bridge_ref_start_pos   |  |   max_tail_bridge_ref_start_pos
	 * (head_chunk_ref_end_pos - num_backsearch)    \  |  |  /  (tail_chunk_ref_start_pos + num_backsearch)
	 *                                               ↓ ↓  ↓ ↓
	 *                                      ref:  -----------------
	 *                               head_chunk → ||||||  |||||| ← tail_chunk
	 *                                    query:  ------..---------
	 *                                               ↑ ↑||↑ ↑
	 * (head_chunk_query_end_pos - num_backsearch)  / / || \ \  (tail_chunk_query_start_pos + num_backsearch)
	 *              min_head_bridge_query_start_pos  /  ||  \  max_tail_bridge_query_start_pos
	 *                                              /   ||   \
	 *                    head_chunk->end_pos_in_query  ||    tail_chunk->query_start_pos(min_tail_bridge_query_start_pos)
	 *    (max_head_bridge_query_start_pos)
	 *                                             cleft_length
	 */


	long min_head_bridge_ref_start_pos = head_chunk->end_pos_in_ref - num_backSearch;
	long min_head_bridge_query_start_pos = head_chunk->end_pos_in_query - num_backSearch;
	int num_bridge_created = 0;
	for(long curr_head_bridge_ref_start_pos = min_head_bridge_ref_start_pos
			, curr_head_bridge_query_start_pos = min_head_bridge_query_start_pos
			; curr_head_bridge_ref_start_pos <= head_chunk->end_pos_in_ref
			; ++curr_head_bridge_ref_start_pos, ++curr_head_bridge_query_start_pos)
	{
		cout << "begin: " << curr_head_bridge_ref_start_pos << ", " << curr_head_bridge_query_start_pos << endl;
		if(curr_head_bridge_query_start_pos + 1 < opt.min_anchor_size) continue;

		//Strand::forward = 1, Strand::reverse = 2
		for(int splice_strand = Strand::forward; splice_strand <= Strand::reverse; ++splice_strand)
		{
			//if((!(opt.strand_mode & Strand_mode::reverse)) && splice_strand != head_chunk->strand) continue;
			//if((!(opt.strand_mode & Strand_mode::forward)) && splice_strand == head_chunk->strand) continue;

			SpliceType::Value head_chunk_splice_type = splice_strand == Strand::forward ? SpliceType::splice_donor : SpliceType::splice_acceptor;
			if(!is_splice_site_by_refPos(ref_SAIndex, curr_head_bridge_ref_start_pos + 1, head_chunk_splice_type, static_cast<Strand::Value>(splice_strand)))
				continue;

			cout << "Get here with strand: " << splice_strand << endl;

			SpliceType::Value tail_chunk_splice_type = splice_strand == Strand::forward ? SpliceType::splice_acceptor : SpliceType::splice_donor;

			long max_tail_bridge_ref_start_pos = tail_chunk->start_pos_in_ref + num_backSearch;
			int max_tail_bridge_query_start_pos = tail_chunk->start_pos_in_query + num_backSearch;
			for(long curr_tail_bridge_ref_end_pos = max_tail_bridge_ref_start_pos
					, curr_tail_bridge_query_end_pos =  max_tail_bridge_query_start_pos
					; curr_tail_bridge_ref_end_pos >= tail_chunk->start_pos_in_ref
					; --curr_tail_bridge_ref_end_pos, --curr_tail_bridge_query_end_pos)
			{
				cout << curr_tail_bridge_ref_end_pos << ", " << curr_tail_bridge_query_end_pos << endl;
				if((query.get_length() - curr_tail_bridge_query_end_pos - 1) < opt.min_anchor_size)
					continue;
				if((curr_tail_bridge_ref_end_pos - curr_head_bridge_ref_start_pos - 1) < (2 * opt.min_intron_size + opt.min_exon_size))
					continue;
				if(curr_tail_bridge_query_end_pos - curr_head_bridge_query_start_pos - 1 < opt.min_exon_size)
					continue;

				cout << "acceptor: " << curr_tail_bridge_ref_end_pos - 1 << endl;
				if(!is_splice_site_by_refPos(ref_SAIndex, curr_tail_bridge_ref_end_pos - 1, tail_chunk_splice_type, static_cast<Strand::Value>(splice_strand)))
					continue;

				/*
				 * Assume num_backsearch = 2                  
				 *                                  curr_head_bridge_ref_start_pos       
				 *                                        \  min_intron_size   
				 *                                         \    |ref_left_bound       min_intron_size     
				 *																          \   |   |    inner_chunk_length   |
				 *                                           \  |   |ref_right_bound|        /  curr_tail_bridge_ref_end_pos
				 *                                            \ |   |          \    |       /  /
				 *                                             ↓←--→↓           ↓←------→↓←--→↓
				 *                                      ref:  ----------------------------------
				 *                               head_chunk → ||||||                 |||||||||||← tail_chunk
				 *                                    query:  ------.................-----------
				 *                                             ↑                              ↑
				 *                                            /                               |
				 *           curr_head_bridge_query_start_pos                 curr_tail_bridge_query_end_pos
				 */

				SeqString inner_chunk_head_ss = get_partner_splice_site(head_chunk_splice_type, static_cast<Strand::Value>(splice_strand));
				SeqString inner_chunk_seq = query.get_infix(curr_head_bridge_query_start_pos + 1, curr_tail_bridge_query_end_pos - 1);
				SeqString inner_chunk_tail_ss = get_partner_splice_site(tail_chunk_splice_type, static_cast<Strand::Value>(splice_strand));
				SeqString inner_chunk_and_ss = inner_chunk_head_ss + inner_chunk_seq + inner_chunk_tail_ss;
				int inner_chunk_length = inner_chunk_seq.get_length();
				long ref_left_bound = curr_head_bridge_ref_start_pos + opt.min_intron_size;
				long ref_right_bound = curr_tail_bridge_ref_end_pos - opt.min_intron_size - inner_chunk_length;
				list<long> anchor_hits_ref_list;

				alnNonspliceOpt opt;
				cout << "bound: " << ref_left_bound << ", " << ref_right_bound << endl;
				collect_anchor_hits_within_bound(inner_chunk_and_ss, anchor_hits_ref_list, ref_SAIndex, ref_left_bound, ref_right_bound, opt);

				cout << anchor_hits_ref_list.size() << endl;

				for(long ref_hit_pos : anchor_hits_ref_list)
				{
					head_chunk->is_last_in_bridge = false;
					int middle_chunk_id = -1;
					WordHitsChunkPtr inner_chunk = make_shared<WordHitsChunk>(middle_chunk_id);
					inner_chunk->strand = head_chunk->strand;
					inner_chunk->hit_refPosNonDec = true;
					inner_chunk->coverage = 1;
					inner_chunk->start_pos_in_ref = ref_hit_pos + 2;
					inner_chunk->end_pos_in_ref = ref_hit_pos + 2 + (inner_chunk_length - 1);
					inner_chunk->start_pos_in_query = curr_head_bridge_query_start_pos + 1;
					inner_chunk->end_pos_in_query = curr_tail_bridge_query_end_pos - 1;
					inner_chunk->is_first_in_bridge = false;
					inner_chunk->is_last_in_bridge = false;
					tail_chunk->is_first_in_bridge = false;
					wordhitschunks.push_back(inner_chunk);

					GapAndMM gap_mm;
					int first_bridge_search_area_mm = (curr_head_bridge_ref_start_pos - head_chunk->end_pos_in_ref <= 0) ? head_chunk_search_area_mm[head_chunk->end_pos_in_ref - curr_head_bridge_ref_start_pos] : 0; //TODO double check
					WordHitsChunkBridgePtr first_bridge = make_shared<WordHitsChunkBridge>(
							head_chunk, inner_chunk
							, curr_head_bridge_ref_start_pos, inner_chunk->start_pos_in_ref
							, curr_head_bridge_query_start_pos, curr_head_bridge_query_start_pos + 1
							, splice_strand, gap_mm, first_bridge_search_area_mm); //adjust_diff = chunks_backsearch_area_diff_sum
					wordhitschunkbridges.push_back(first_bridge);

					int second_bridge_search_area_mm = (curr_tail_bridge_ref_end_pos - tail_chunk->start_pos_in_ref >= 0) ? tail_chunk_search_area_mm[curr_tail_bridge_ref_end_pos - tail_chunk->start_pos_in_ref] : 0; //TODO double check
					WordHitsChunkBridgePtr second_bridge = make_shared<WordHitsChunkBridge>(
							inner_chunk, head_chunk
							, inner_chunk->end_pos_in_ref, curr_tail_bridge_ref_end_pos
							, inner_chunk->end_pos_in_query, inner_chunk->end_pos_in_query + 1
							, splice_strand, gap_mm, second_bridge_search_area_mm); //adjust_diff = chunks_backsearch_area_diff_sum
					wordhitschunkbridges.push_back(second_bridge);

					num_bridge_created++;
				}
			}
		}
	}
	return num_bridge_created;
}

void cal_two_wordchunks_backsearch_area_mm(const WordHitsChunkPtr head_chunk, const WordHitsChunkPtr tail_chunk, vector<int>& head_chunk_search_area_diff, vector<int>& tail_chunk_search_area_mm, const SeqString query, const SeqSuffixArray& ref_SAIndex, int num_backSearch)
{
	head_chunk_search_area_diff = vector<int>(num_backSearch + 1);
	tail_chunk_search_area_mm = vector<int>(num_backSearch + 1);
	int head_chunk_diff = 0;
	int tail_chunk_diff = 0;
	for(int i = 0; i < num_backSearch + 1; ++i)
	{
		long head_chunk_queryEnd = head_chunk->end_pos_in_query - i;
		long head_chunk_refEnd = head_chunk->end_pos_in_ref - i;
		if(query[head_chunk_queryEnd] != ref_SAIndex.char_at(head_chunk_refEnd))
		{
			++head_chunk_diff;
		}
		head_chunk_search_area_diff[i] = head_chunk_diff;

		long tail_chunk_refEnd = tail_chunk->start_pos_in_ref + i;
		long tail_chunk_queryEnd = tail_chunk->start_pos_in_query + i;
		if(query[tail_chunk_queryEnd] != ref_SAIndex.char_at(tail_chunk_refEnd))
		{
			++tail_chunk_diff;
		}
		tail_chunk_search_area_mm[i] = tail_chunk_diff;
	}
}
