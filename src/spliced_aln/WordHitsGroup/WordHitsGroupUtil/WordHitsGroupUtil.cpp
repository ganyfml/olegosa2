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
	cout << endl;
	return head_chunk_diff + tail_chunk_diff;
}

int locate_bridge_within_two_chunks_denovo(WordHitsChunkPtr& head_chunk, WordHitsChunkPtr& tail_chunk, std::list<WordHitsChunkBridgePtr>& wordhitschunkbridges, int num_backSearch, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
	WordHitsChunkBridgePtr bridge_to_be_added;
	int num_bridge_found = 0;

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
				++num_bridge_found;
			}
		}
	}

	if(opt.report_best_only && bridge_to_be_added != nullptr)
	{
		wordhitschunkbridges.push_back(bridge_to_be_added);
		++num_bridge_found;
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
