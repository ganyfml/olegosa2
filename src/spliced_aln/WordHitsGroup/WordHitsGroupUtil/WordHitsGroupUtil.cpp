// vim: set noexpandtab tabstop=2:

#include <spliced_aln/WordHitsGroupUtil.hpp>
#include <spliced_aln/aln_global.hpp>

using namespace std;

Strand::Value determin_strand_by_canonical_spliceSite(const SeqSuffixArray& ref_SAIndex, long donor_pos, long acceptor_pos)
{
	if(ref_SAIndex.char_at(donor_pos) == 'G' && ref_SAIndex.char_at(donor_pos + 1) == 'T'
			&& ref_SAIndex.char_at(acceptor_pos - 1) == 'A' && ref_SAIndex.char_at(acceptor_pos) == 'G')
	{
		return Strand::forward;
	}
	else if(ref_SAIndex.char_at(donor_pos) == 'C' && ref_SAIndex.char_at(donor_pos + 1) == 'T'
			&& ref_SAIndex.char_at(acceptor_pos - 1) == 'A' && ref_SAIndex.char_at(acceptor_pos) == 'C')
	{
		return Strand::reverse;
	}
	return Strand::none_decide;
}

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
	int num_bridge_found = 0;

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
				++num_bridge_found;
			}
		}
	}

	if(opt.report_best_only && bridge_to_be_added != nullptr)
	{
		wordhitschunkbridges.push_back(bridge_to_be_added);
		num_bridge_found = 1;
	}
	return num_bridge_found;
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
