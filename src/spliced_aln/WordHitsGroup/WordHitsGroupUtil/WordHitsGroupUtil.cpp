// vim: set noexpandtab tabstop=2:

#include <spliced_aln/WordHitsGroupUtil.hpp>
#include <spliced_aln/aln_global.hpp>
#include <nonspliced_aln/nonsplicedAln.hpp>
#include <list>

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
	int cleft_length = tail_chunk->start_pos_in_query - head_chunk->end_pos_in_query - 1;
	if(cleft_length + 2 * num_backSearch <= 0) return 0;
	if((tail_chunk->start_pos_in_ref - head_chunk->end_pos_in_ref - 1) < (tail_chunk->start_pos_in_query - head_chunk->end_pos_in_query - 1)) return 0;

	long min_bridge_ref_start_pos = head_chunk->end_pos_in_ref - num_backSearch;
	long max_bridge_ref_start_pos = head_chunk->end_pos_in_ref + cleft_length + num_backSearch + 1;
	long min_bridge_query_start_pos = head_chunk->end_pos_in_query - num_backSearch;
	long max_bridge_query_end_pos = head_chunk->end_pos_in_query + cleft_length + num_backSearch + 1;
	SeqString search_query = query.get_infix(min_bridge_query_start_pos + 1, max_bridge_query_end_pos - 1);

	for(long curr_bridge_ref_start_pos = min_bridge_ref_start_pos
			, curr_bridge_ref_end_pos = tail_chunk->start_pos_in_ref - num_backSearch - cleft_length
			, curr_bridge_query_start_pos = min_bridge_query_start_pos
			; curr_bridge_ref_start_pos < max_bridge_ref_start_pos
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
					, splice_strand, original_gapMM_sum);
			new_bridge->gap_mm = search_area_gap_mm_with_bridge;
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
	std::list<AlnResult> anchor_hit_result;
	nonsplicedAln(inner_chunk_and_ss, anchor_hit_result, ref_SAIndex, anchor_search_opt);
	while(!anchor_hit_result.empty())
	{
		AlnResult a = anchor_hit_result.front();
		anchor_hit_result.pop_front();
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

inline bool is_donor_splice_site_forward(const SeqSuffixArray& ref, long ref_pos)
{
	return ref.char_at(ref_pos) == 'G' && ref.char_at(ref_pos + 1) == 'T';
}

inline bool is_donor_splice_site_reverse(const SeqSuffixArray& ref, long ref_pos)
{
	return ref.char_at(ref_pos) == 'C' && ref.char_at(ref_pos + 1) == 'T';
}

inline bool is_acceptor_splice_site_forward(const SeqSuffixArray& ref, long ref_pos)
{
	return ref.char_at(ref_pos) == 'A' && ref.char_at(ref_pos + 1) == 'G';
}

inline bool is_acceptor_splice_site_reverse(const SeqSuffixArray& ref, long ref_pos)
{
	return ref.char_at(ref_pos) == 'A' && ref.char_at(ref_pos + 1) == 'C';
}

inline bool is_splice_site(const SeqSuffixArray& ref, long ref_pos, int splice_type, bool forward_strand)
{
	if(splice_type == SpliceType::splice_donor)
	{
		if(forward_strand)
			return is_donor_splice_site_forward(ref, ref_pos);
		else
			return is_donor_splice_site_reverse(ref, ref_pos);
	}
	else if(splice_type == SpliceType::splice_acceptor)
	{
		if(forward_strand)
			return is_acceptor_splice_site_forward(ref, ref_pos);
		else
			return is_acceptor_splice_site_reverse(ref, ref_pos);
	}
	else
		return false;
}

Strand::Value determin_strand_by_canonical_spliceSite(const SeqSuffixArray& ref_SAIndex, long donor_pos, long acceptor_pos)
{
	if(is_donor_splice_site_forward(ref_SAIndex, donor_pos) && is_acceptor_splice_site_forward(ref_SAIndex, acceptor_pos - 1))
	{
		return Strand::forward;
	}
	if(is_donor_splice_site_reverse(ref_SAIndex, donor_pos) && is_acceptor_splice_site_reverse(ref_SAIndex, acceptor_pos - 1))
	{
		return Strand::reverse;
	}
	return Strand::none_decide;
}

bool is_splice_site_by_refPos(const SeqSuffixArray& ref, long ref_pos, SpliceType::Value splice_type, Strand::Value splice_strand)
{
	bool forward_strand;
	if(splice_strand == Strand::none_decide)
		return false;
	else
		forward_strand = (splice_strand == Strand::forward);

	if((splice_strand == Strand::forward && splice_type == SpliceType::splice_donor)
			|| (splice_strand == Strand::reverse && splice_type == SpliceType::splice_acceptor))
	{
		return is_splice_site(ref, ref_pos, splice_type, forward_strand);
	}
	else
	{
		return is_splice_site(ref, ref_pos - 1, splice_type, forward_strand);
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
	 *                                               ↑ ↑  ↑ ↑
	 * (head_chunk_query_end_pos - num_backsearch)  / /    \ \  (tail_chunk_query_start_pos + num_backsearch)
	 *              min_head_bridge_query_start_pos  /      \  max_tail_bridge_query_start_pos
	 *                                              /        \
	 *                    head_chunk->end_pos_in_query        tail_chunk->query_start_pos(min_tail_bridge_query_start_pos)
	 *    (max_head_bridge_query_start_pos)
	 */


	long min_head_bridge_ref_start_pos = head_chunk->end_pos_in_ref - num_backSearch;
	long min_head_bridge_query_start_pos = head_chunk->end_pos_in_query - num_backSearch;
	int num_alignment = 0;

	long curr_head_bridge_ref_start_pos;
	int curr_head_bridge_query_start_pos;
	for(curr_head_bridge_ref_start_pos = min_head_bridge_ref_start_pos
			, curr_head_bridge_query_start_pos = min_head_bridge_query_start_pos
			; curr_head_bridge_ref_start_pos <= head_chunk->end_pos_in_ref
			; ++curr_head_bridge_ref_start_pos, ++curr_head_bridge_query_start_pos)
	{
		if(curr_head_bridge_query_start_pos + 1 < opt.min_anchor_size) continue;

		for(Strand::Value splice_strand : list<Strand::Value>{Strand::forward, Strand::reverse})
		{
			//if((!(opt.strand_mode & Strand_mode::reverse)) && splice_strand != head_chunk->strand) continue;
			//if((!(opt.strand_mode & Strand_mode::forward)) && splice_strand == head_chunk->strand) continue;

			SpliceType::Value head_chunk_splice_type = splice_strand == Strand::forward ? SpliceType::splice_donor : SpliceType::splice_acceptor;
			if(!is_splice_site_by_refPos(ref_SAIndex, curr_head_bridge_ref_start_pos + 1, head_chunk_splice_type, splice_strand))
				continue;

			SpliceType::Value tail_chunk_splice_type = splice_strand == Strand::forward ? SpliceType::splice_acceptor : SpliceType::splice_donor;

			SeqString inner_chunk_head_ss = get_partner_splice_site(head_chunk_splice_type, splice_strand);
			SeqString inner_chunk_tail_ss = get_partner_splice_site(tail_chunk_splice_type, splice_strand);
			long ref_left_bound = curr_head_bridge_ref_start_pos + opt.min_intron_size;

			long max_tail_bridge_ref_start_pos = tail_chunk->start_pos_in_ref + num_backSearch;
			int max_tail_bridge_query_start_pos = tail_chunk->start_pos_in_query + num_backSearch;

			long curr_tail_bridge_ref_end_pos;
			int curr_tail_bridge_query_end_pos;
			for(curr_tail_bridge_ref_end_pos = max_tail_bridge_ref_start_pos
					, curr_tail_bridge_query_end_pos =  max_tail_bridge_query_start_pos
					; curr_tail_bridge_ref_end_pos >= tail_chunk->start_pos_in_ref
					; --curr_tail_bridge_ref_end_pos, --curr_tail_bridge_query_end_pos)
			{
				if((query.get_length() - curr_tail_bridge_query_end_pos - 1) < opt.min_anchor_size)
					continue;
				if((curr_tail_bridge_ref_end_pos - curr_head_bridge_ref_start_pos - 1) < (2 * opt.min_intron_size + opt.min_exon_size))
					continue; 
				if(curr_tail_bridge_query_end_pos - curr_head_bridge_query_start_pos - 1 < opt.min_exon_size)
					continue;

				if(!is_splice_site_by_refPos(ref_SAIndex, curr_tail_bridge_ref_end_pos - 1, tail_chunk_splice_type, splice_strand))
					continue;

				/*
				 * Assume num_backsearch = 2                  
				 *                                  curr_head_bridge_ref_start_pos       
				 *                                        \  min_intron_size   
				 *                                         \      │  ref_left_bound        min_intron_size     
				 *                                          \     │   |     inner_chunk_length  |
				 *                                           \    │   | ref_right_bound│       /  curr_tail_bridge_ref_end_pos
				 *                                            \   │   /          \     │      │   /
				 *                                             ↓┌─┴─┐↓            ↓┌───┴───┐┌─┴─┐↓
				 *                                      ref:  ------------------------------------
				 *                               head_chunk → ||||||  ⋮⋮⋮⋮⋮⋮⋮⋮⋮     ||||||||||||||← tail_chunk
				 *                                    query:  ------..---------.....--------------
				 *                                             ↑      └───┬───┘                  ↑
				 *                                            /      inner_chunk                 |
				 *           curr_head_bridge_query_start_pos                             curr_tail_bridge_query_end_pos
				 */

				SeqString inner_chunk_seq = query.get_infix(curr_head_bridge_query_start_pos + 1, curr_tail_bridge_query_end_pos - 1);
				SeqString inner_chunk_and_ss = inner_chunk_head_ss + inner_chunk_seq + inner_chunk_tail_ss;
				int inner_chunk_length = inner_chunk_seq.get_length();
				long ref_right_bound = curr_tail_bridge_ref_end_pos - opt.min_intron_size - inner_chunk_length;
				list<long> inner_chunk_and_ss_hits_ref_list;

				alnNonspliceOpt opt;
				collect_anchor_hits_within_bound(inner_chunk_and_ss, inner_chunk_and_ss_hits_ref_list, ref_SAIndex, ref_left_bound, ref_right_bound, opt);

				for(long ref_hit_pos : inner_chunk_and_ss_hits_ref_list)
				{
					head_chunk->is_last_in_bridge = false;
					tail_chunk->is_first_in_bridge = false;

					WordHitsChunkPtr inner_chunk = make_shared<WordHitsChunk>(
							head_chunk->strand
							, ref_hit_pos + 2, ref_hit_pos + 2 + (inner_chunk_length - 1)
							, curr_head_bridge_query_start_pos + 1, curr_tail_bridge_query_end_pos - 1);
					wordhitschunks.push_back(inner_chunk);

					int head_bridge_search_area_mm = (curr_head_bridge_ref_start_pos - head_chunk->end_pos_in_ref <= 0) ? head_chunk_search_area_mm[head_chunk->end_pos_in_ref - curr_head_bridge_ref_start_pos] : 0;
					WordHitsChunkBridgePtr head_bridge = make_shared<WordHitsChunkBridge>(
							head_chunk, inner_chunk
							, curr_head_bridge_ref_start_pos, inner_chunk->start_pos_in_ref
							, curr_head_bridge_query_start_pos, curr_head_bridge_query_start_pos + 1
							, splice_strand, head_bridge_search_area_mm);
					wordhitschunkbridges.push_back(head_bridge);

					int tail_bridge_search_area_mm = (curr_tail_bridge_ref_end_pos - tail_chunk->start_pos_in_ref >= 0) ? tail_chunk_search_area_mm[curr_tail_bridge_ref_end_pos - tail_chunk->start_pos_in_ref] : 0;
					WordHitsChunkBridgePtr tail_bridge = make_shared<WordHitsChunkBridge>(
							inner_chunk, head_chunk
							, inner_chunk->end_pos_in_ref, curr_tail_bridge_ref_end_pos
							, inner_chunk->end_pos_in_query, inner_chunk->end_pos_in_query + 1
							, splice_strand, tail_bridge_search_area_mm);
					wordhitschunkbridges.push_back(tail_bridge);

					++num_alignment;
				}
			}
		}
	}
	return num_alignment;
}

void update_aln_list(list<WordHitsChunkBridgeChainPtr>& results, vector<bool>& destroy_flag, int& aln_length)
{
	auto aln_iter = results.begin();
	for(int i = 0; i < aln_length; ++i)
	{
		if(destroy_flag[i])
		{
			aln_iter = results.erase(aln_iter);
		}
		else
		{
			++aln_iter;
		}
	}
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

void concat_bridges(std::list<WordHitsChunkBridgePtr>& wordhitschunkbridges, list<WordHitsChunkBridgeChainPtr>& results, int query_length, bool global)
{
	if(wordhitschunkbridges.size() == 0)
		return;

	wordhitschunkbridges.sort(compare_wordHitsChunkBridgeByRefAndStrand);
	WordHitsChunkBridgeChainPtr init_chunk = make_shared<WordHitsChunkBridgeChain>();
	init_chunk->bridges.push_back(wordhitschunkbridges.front());
	results.push_back(init_chunk);

	/*
	 * ====..........====..............(init_chunk) ┐
	 *    └──────────┘                              │
	 *                                              │
	 * ====.............====...........             │
	 *    └─────────────┘                           ├─ push to results (bridges which has the same head_chunk with init_chunk)
	 *                                              │
	 * ====................====........             │
	 *    └────────────────┘                        ┘
	 *
	 * .....====..............====...
	 *         └──────────────┘
	 *
	 * .....====................====...
	 *         └────────────────┘
	 */

	auto curr_bridge_iter = ++wordhitschunkbridges.begin();
	for(WordHitsChunkBridgePtr begin_bridge_iter = wordhitschunkbridges.front(); curr_bridge_iter != wordhitschunkbridges.end(); ++curr_bridge_iter)
	{
		if((*curr_bridge_iter)->head_chunk == begin_bridge_iter->head_chunk && (*curr_bridge_iter)->spliced_strand == begin_bridge_iter->spliced_strand)
		{
			WordHitsChunkBridgeChainPtr r = make_shared<WordHitsChunkBridgeChain>();
			r->bridges.push_back(*curr_bridge_iter);
			results.push_back(r);
		}
		else
		{
			break;
		}
	}

	int prev_aln_length = results.size();
	vector<bool>destroy_flag(prev_aln_length, false);

	bool need_to_update_aln_list = false;
	auto prev_bridge_iter = curr_bridge_iter;
	prev_bridge_iter--;
	for(; curr_bridge_iter != wordhitschunkbridges.end(); ++prev_bridge_iter, ++curr_bridge_iter)
	{
		WordHitsChunkBridgePtr prev_bridge = *prev_bridge_iter;
		WordHitsChunkBridgePtr curr_bridge = *curr_bridge_iter;

		if(curr_bridge->head_chunk != prev_bridge->head_chunk && need_to_update_aln_list)
		{
			update_aln_list(results, destroy_flag, prev_aln_length);
			prev_aln_length = results.size();
			destroy_flag.resize(prev_aln_length, false);
			need_to_update_aln_list = false;
		}

		/*
		 * ..........====..........====....(curr_bridge_iter)
		 *              └──────────┘ 
		 *
		 * --------------------------------------------------
		 *
		 * ====.............====...........     ┐
		 *    └─────────────┘                   │
		 *                                      │
		 * ====......====..................(#)  │
		 *    └──────┘                          │
		 *                                      ├─ results
		 * ====...........====...               │
		 *    └───────────┘                     │
		 *                                      │
		 * ====................====...          │
		 *    └────────────────┘                ┘
		 *
		 * Iter all results to find the one can be extened with curr_bridge_iter, for example,
		 * (#) can be extended with curr_bridge_iter
		 */

		bool curr_bridge_extended = false;

		{
			auto aln_iter = results.begin();
			int aln_index = 0;
			for(; aln_index < prev_aln_length; ++aln_iter, ++aln_index)
			{
				WordHitsChunkBridgePtr aln_last_bridge = (*aln_iter)->bridges.back();
				if(aln_last_bridge->tail_chunk == curr_bridge->head_chunk && aln_last_bridge->spliced_strand == curr_bridge->spliced_strand && aln_last_bridge->start_pos_in_query < curr_bridge->start_pos_in_query)
				{

					/*
					 *            head_chunk     tail_chunk
					 * ..............====..........====
					 *                  └────┬─────┘
					 *                    curr_bridge
					 *
					 * head_chunk    tail_chunk
					 * ====..........====..............
					 *    └────┬─────┘
					 *      aln_iter
					 *
					 * ↓
					 *
					 * extended_result:
					 *
					 * ===...........====..........====
					 *   └─────┬─────┘  └────┬─────┘
					 *   aln_last_bridge curr_bridge
					 */

					WordHitsChunkBridgeChainPtr extended_result = make_shared<WordHitsChunkBridgeChain>();
					extended_result->bridges = list<WordHitsChunkBridgePtr>((*aln_iter)->bridges.begin(), (*aln_iter)->bridges.end());
					extended_result->bridges.push_back(curr_bridge);
					results.push_back(extended_result);
					need_to_update_aln_list = true;
					curr_bridge_extended = true;
					//FIXME this if may not be useful
					if(aln_last_bridge->tail_chunk->end_pos_in_query != query_length - 1)
					{
						destroy_flag[aln_index] = true;
					}
				}
			}
		}

		if(!curr_bridge_extended || curr_bridge->head_chunk->start_pos_in_query == 0)
		{
			WordHitsChunkBridgeChainPtr r = make_shared<WordHitsChunkBridgeChain>();
			r->bridges.push_back(curr_bridge);
			results.push_back(r);
			need_to_update_aln_list = true;
		}
	}

	if(need_to_update_aln_list)
	{
		update_aln_list(results, destroy_flag, prev_aln_length);
		prev_aln_length = results.size();
		destroy_flag.resize(prev_aln_length, false);
	}
	summarize_WordHitsChunkBridgeChains(results, query_length, global);
}

void locate_bridge_two_chunks(WordHitsChunkPtr& head_chunk, WordHitsChunkPtr& tail_chunk, list<WordHitsChunkBridgePtr>& wordhitschunkbridges, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
	//Determin Number of BackSearch
	int num_backSearch = opt.max_overhang;

	//when sequences extends beyond splice sites by chance, we can increase the overhang
	int query_cleft = head_chunk->end_pos_in_query - tail_chunk->start_pos_in_query + 1;
	num_backSearch = num_backSearch < query_cleft ? query_cleft : num_backSearch;

	int head_chunk_len = head_chunk->end_pos_in_query - head_chunk->start_pos_in_query + 1;
	num_backSearch = num_backSearch >= head_chunk_len - 4 ? head_chunk_len - 4 : num_backSearch;

	if(opt.denovo_search &&
			(tail_chunk->start_pos_in_ref - 1 - head_chunk->end_pos_in_ref < opt.max_intron_size))
	{
		locate_bridge_within_two_chunks_denovo(head_chunk, tail_chunk, wordhitschunkbridges, num_backSearch, query, ref_SAIndex, opt);
	}

	//	int locate_bridge_within_two_chunks_with_inner_exon_denovo(WordHitsChunkPtr& head_chunk, WordHitsChunkPtr& tail_chunk, std::list<WordHitsChunkBridgePtr>& wordhitschunkbridges, std::list<WordHitsChunkPtr>& wordhitschunks, int num_backSearch, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt);

}
