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
	cout << endl;
	return head_chunk_diff + tail_chunk_diff;
}

int locate_bridge_within_two_chunks_denovo(WordHitsChunkPtr& head_chunk, WordHitsChunkPtr& tail_chunk, std::list<WordHitsChunkBridgePtr>& wordhitschunkbridges, int num_backSearch, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
	WordHitsChunkBridgePtr bridge_to_be_added;
	int num_bridge_created = 0;

	int local_max_diff = opt.local_wordChunk_diff;
	int best_diff = local_max_diff + 1;

	/*
	 * Assume num_backsearch = 2
	 *                                         head_chunk_ref_end_pos
	 *                                                 |
	 *                      min_bridge_ref_start_pos   |   max_bridge_ref_start_pos
	 * (head_chunk_ref_end_pos - num_backsearch)    \  |    /    (head_chunk_ref_end_pos + cleft_length + num_backsearch)
	 *                                               ↓ ↓   ↓
	 *                                      ref:  -----------------
	 *                               head_chunk → ||||||  |||||| ← tail_chunk
	 *                                    query:  ------..---------
	 *                                               ↑ ↑|| ↑
	 * (head_chunk_query_end_pos - num_backsearch)  / / ||  \    (head_chunk_query_end_pos + cleft_length + num_backsearch)
	 *                   min_bridge_query_start_pos  /  ||   max_bridge_query_start_pos
	 *                                              /   ||
	 *                      head_chunk_query_end_pos    ||
	 *                                             cleft_length
	 */

	int chunks_backsearch_area_diff_sum = cal_two_wordchunks_backsearch_area_diff_sum(head_chunk, tail_chunk, query, ref_SAIndex, num_backSearch);
	long min_bridge_ref_start_pos = head_chunk->end_pos_in_ref - num_backSearch;
	long max_bridge_ref_start_pos = head_chunk->end_pos_in_ref + (tail_chunk->start_pos_in_query - head_chunk->end_pos_in_query - 1) + num_backSearch;
	long cleft_and_backsearch_length = max_bridge_ref_start_pos - min_bridge_ref_start_pos; //none symmetric search region length
	long min_bridge_query_start_pos = head_chunk->end_pos_in_query - num_backSearch;

	for(long curr_bridge_ref_start_pos = min_bridge_ref_start_pos
			, curr_bridge_ref_end_pos = tail_chunk->start_pos_in_ref + num_backSearch - cleft_and_backsearch_length
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

		SeqString gap_ref = ref_SAIndex.get_infixSeq(min_bridge_ref_start_pos + 1, curr_bridge_ref_start_pos) + ref_SAIndex.get_infixSeq(curr_bridge_ref_end_pos, tail_chunk->start_pos_in_ref + num_backSearch - 1);
		SeqString gap_query = query.get_infix(min_bridge_query_start_pos + 1, min_bridge_query_start_pos + 1 + (tail_chunk->start_pos_in_query - head_chunk->end_pos_in_query - 1) + 1);

		GapAndMM gap_mm;
		aln_global(gap_ref, gap_query, gap_mm);
		int diff = gap_mm.total_diff() - chunks_backsearch_area_diff_sum;

		/*
		 *                                              search_area
		 *                                      ref: -----------------
		 *                      orginal_head_chunk → ||||||     |||||| ← orginal_tail_chunk
		 *                          new_head_chunk → ||||     |||||||| ← new_tail_chunk
		 *                                    query: -------...-------
		 *                                    
		 *                          original_diff = (orginal_head_chunk + orginal_tail_chunk) vs query
		 *                          bridge_diff = (new_head_chunk + new_tail_chunk) vs query
		 *                                 diff = bridge_diff - original_diff
		 */

		if(diff < local_max_diff)
		{
			WordHitsChunkBridgePtr new_bridge = make_shared<WordHitsChunkBridge>(
					head_chunk, tail_chunk
					, curr_bridge_ref_start_pos, curr_bridge_ref_end_pos
					, curr_bridge_query_start_pos, curr_bridge_query_start_pos + 1
					, splice_strand, gap_mm, chunks_backsearch_area_diff_sum); //adjust_diff = chunks_backsearch_area_diff_sum 
			head_chunk->is_first_in_bridge = false;
			tail_chunk->is_last_in_bridge = false;
			if(opt.report_best_only && diff < best_diff)
			{
				bridge_to_be_added = new_bridge;
				best_diff = diff;
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
		++num_bridge_created;
	}
	return num_bridge_created;
}

void collect_anchor_hits_within_bound(const SeqString& anchor_seq, list<long>& anchor_hit_list, const SeqSuffixArray& ref_SAIndex, long hit_left_bound, long hit_right_bound, const alnNonspliceOpt& anchor_search_opt)
{
	std::queue<AlnResult> anchor_hit_result;
	nonsplicedAln(anchor_seq, anchor_hit_result, ref_SAIndex, anchor_search_opt);
	while(!anchor_hit_result.empty())
	{
		AlnResult a = anchor_hit_result.front();
		anchor_hit_result.pop();
		for(unsigned long i = a.SA_index_low; i < a.SA_index_high; ++i)
		{
			long ref_hit_pos =  ref_SAIndex.SAIndex2SeqPos(i);
			if(ref_hit_pos >= hit_left_bound
					&& ((ref_hit_pos + anchor_seq.get_length() - 1) <= hit_right_bound))
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

int locate_bridge_within_two_chunks_with_inner_exon_denovo(WordHitsChunkPtr& head_chunk, WordHitsChunkPtr& tail_chunk, std::list<WordHitsChunkBridgePtr>& wordhitschunkbridges, int num_backSearch, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
	vector<int> head_chunk_adjust_diff;
	vector<int> tail_chunk_adjust_diff;
	cal_two_wordChunks_adjust_diff(head_chunk, tail_chunk, head_chunk_adjust_diff, tail_chunk_adjust_diff, query, ref_SAIndex, num_backSearch);

	int num_bridge_created = 0;
	for(long curr_bridge_ref_start_pos = min_headChunk_refEnd
			, curr_bridge_query_start_pos = head_chunk->queryEnd_pos - num_backSearch
			; curr_bridge_ref_start_pos <= max_headChunk_refEnd
			; ++curr_bridge_ref_start_pos, ++ curr_bridge_query_start_pos)
	{
		if(curr_bridge_query_start_pos + 1 < opt.min_anchor_size) continue;

		for(int splice_strand = 0; splice_strand < 2; ++splice_strand)
		{
			if((!(opt.strand_mode & Strand_mode::reverse)) && splice_strand != head_chunk->strand) continue;
			if((!(opt.strand_mode & Strand_mode::forward)) && splice_strand == head_chunk->strand) continue;

			int head_chunk_splice_type = splice_strand ? SpliceType::SPLICE_DONOR : SpliceType::SPLICE_ACCEPTOR;
			if((annotation->retrieve_spliceSite(curr_bridge_ref_start_pos + 1, splice_strand, head_chunk_splice_type) == nullptr)
					&& (!is_splice_site_by_refPos(ref_SAIndex, curr_bridge_ref_start_pos + 1, head_chunk_splice_type, splice_strand))) continue; //TODO + 1 issue

			int tail_chunk_splice_type = splice_strand ? SpliceType::SPLICE_ACCEPTOR : SpliceType::SPLICE_DONOR;
			for(long tailChunk_refStart = tail_chunk->refStart_pos + num_backSearch, tailChunk_queryStart = tail_chunk->queryStart_pos + num_backSearch
					; tailChunk_refStart >= tail_chunk->refStart_pos
					; --tailChunk_refStart, --tailChunk_queryStart)
			{
				if(tailChunk_refStart - curr_bridge_ref_start_pos < 2 * opt.min_intron_size + opt.min_exon_size ) continue;
				if((query.get_length() - tailChunk_queryStart) < opt.min_anchor_size) continue;
				int query_gap = tailChunk_queryStart - curr_bridge_query_start_pos;
				if(query_gap + 1 < opt.min_exon_size) continue;

				if((annotation->retrieve_spliceSite(tailChunk_refStart - 1, splice_strand, tail_chunk_splice_type) == nullptr)
						&& (!is_splice_site_by_refPos(ref_SAIndex, tailChunk_refStart - 1, tail_chunk_splice_type, splice_strand))) continue; //TODO + 1 issue

				SeqString gap_head_ss = get_partner_splice_site(head_chunk_splice_type, splice_strand);
				SeqString gap_middle = query.get_infix(curr_bridge_query_start_pos, tailChunk_queryStart);
				SeqString gap_tail_ss = get_partner_splice_site(tail_chunk_splice_type, splice_strand);
				SeqString anchor_seq = gap_head_ss + gap_middle + gap_tail_ss;
				int anchor_length = anchor_seq.get_length();
				long ref_left_bound = curr_bridge_ref_start_pos + opt.min_intron_size;
				long ref_right_bound = tailChunk_refStart - opt.min_intron_size - anchor_length;
				list<long> anchor_hits_ref_list;

				alnNonspliceOpt opt;
				collect_anchor_hits(anchor_seq, anchor_hits_ref_list, ref_SAIndex, ref_left_bound, ref_right_bound, opt); //TODO strand? Why only accept strand = 0

				for(long ref_hit_pos : anchor_hits_ref_list)
				{
					head_chunk->is_last = false;
					int middle_chunk_id = -1;
					WordHitsChunkPtr middle_chunk = make_shared<WordHitsChunk>(middle_chunk_id);
					middle_chunk->strand = head_chunk->strand;
					middle_chunk->colinearity = true;
					middle_chunk->coverage = 1;
					middle_chunk->refStart_pos = ref_hit_pos + 2;
					middle_chunk->refEnd_pos = middle_chunk->refStart_pos + anchor_length - 1;
					middle_chunk->queryStart_pos = curr_bridge_query_start_pos;
					middle_chunk->queryEnd_pos = tailChunk_queryStart;
					middle_chunk->is_first = false;
					middle_chunk->is_last = false;
					tail_chunk->is_first = false;
					wordhitschunks.push_back(middle_chunk);

					WordHitsChunkBridgePtr first_bridge = make_shared<WordHitsChunkBridge>();
					first_bridge->head_chunk = head_chunk;
					first_bridge->tail_chunk = middle_chunk;
					first_bridge->refStart_pos = curr_bridge_ref_start_pos;
					first_bridge->refEnd_pos = middle_chunk->refStart_pos;
					first_bridge->queryStart_pos = curr_bridge_query_start_pos;
					first_bridge->queryEnd_pos = first_bridge->queryStart_pos + 1;
					first_bridge->adjust_diff = (curr_bridge_ref_start_pos - head_chunk->refEnd_pos <= 0) ? head_chunk_adjust_diff[head_chunk->refEnd_pos - curr_bridge_ref_start_pos] : 0; //TODO double check
					first_bridge->splice_strand = splice_strand;
					first_bridge->score = cal_splice_score(ref_SAIndex, curr_bridge_ref_start_pos, middle_chunk->refStart_pos);
					wordhitschunkbridge.push_back(first_bridge);

					WordHitsChunkBridgePtr second_bridge = make_shared<WordHitsChunkBridge>();
					second_bridge->head_chunk = middle_chunk;
					second_bridge->tail_chunk = tail_chunk;
					second_bridge->refStart_pos = middle_chunk->refEnd_pos;
					second_bridge->refEnd_pos = tailChunk_refStart;
					second_bridge->queryStart_pos = middle_chunk->queryStart_pos;
					second_bridge->queryEnd_pos = second_bridge->queryStart_pos + 1;
					second_bridge->adjust_diff = (tailChunk_refStart - tail_chunk->refStart_pos >= 0) ? tail_chunk_adjust_diff[tailChunk_refStart - tail_chunk->refStart_pos] : 0; //TODO double check
					second_bridge->splice_strand = splice_strand;
					second_bridge->score = cal_splice_score(ref_SAIndex, curr_bridge_ref_start_pos, middle_chunk->refStart_pos);
					wordhitschunkbridge.push_back(second_bridge);

					wordhitschunkbridge.push_back(second_bridge);
					num_bridge_created++;
				}
			}
		}
	}
	return num_bridge_created;
}

//BACKUP
/*
	 void cal_two_wordChunks_adjust_diff(const WordHitsChunkPtr head_chunk, const WordHitsChunkPtr tail_chunk, vector<int>& head_chunk_adjust_diff, vector<int>& tail_chunk_adjust_diff, const SeqString query, const SeqSuffixArray& ref_SAIndex, int num_backSearch)
	 {
	 head_chunk_adjust_diff = vector<int>(num_backSearch + 1);
	 tail_chunk_adjust_diff = vector<int>(num_backSearch + 1);
	 int head_chunk_diff = 0;
	 int tail_chunk_diff = 0;
	 for(int i = 0; i < num_backSearch + 1; ++i)
	 {
	 long head_chunk_queryEnd = head_chunk->end_pos_in_query - i;
	 if(query[head_chunk_queryEnd] != ref_SAIndex.char_at(head_chunk_refEnd))
	 {
	 ++head_chunk_diff;
	 }
	 head_chunk_adjust_diff[i] = head_chunk_diff;

	 long tail_chunk_refEnd = tail_chunk->start_pos_in_ref + i;
	 long tail_chunk_queryEnd = tail_chunk->start_pos_in_query + i;
	 if(query[tail_chunk_queryEnd] != ref_SAIndex.char_at(tail_chunk_refEnd))
	 {
	 ++tail_chunk_diff;
	 }
	 tail_chunk_adjust_diff[i] = tail_chunk_diff;
	 }
	 }*/
