// vim: set noexpandtab tabstop=2:

#include <spliced_aln/WordHitsGroup.hpp>
#include <spliced_aln/WordHitsGroupUtil.hpp>
#include <spliced_aln/aln_global.hpp>
#include <vector>

using namespace std;

bool compare_wordHitsGroupByScore(const WordHitsGroupPtr group1, const WordHitsGroupPtr group2)
{
	return group1->score < group2->score;
}

void WordHitsGroup::group_wordHits_wordChunks(const AlnSpliceOpt& opt, int num_words)
{
	vector<int> words_occ(num_words);
	for(auto iter = wordhits.begin(); iter != wordhits.end(); ++iter)
	{
		++words_occ[(*iter)->word_id];
	}

	long prev_hit_diag = -1;
	int local_wordChunk_diff = opt.local_wordChunk_diff;

	int curr_wordChunk_id = 0;
	WordHitsChunkPtr curr_chunk;
	for(auto iter = wordhits.begin(); iter != wordhits.end(); ++iter)
	{
		if(words_occ[(*iter)->word_id] > 1)
			continue;

		long curr_hit_diag = (*iter)->ref_pos - (*iter)->query_pos;
		if(prev_hit_diag == -1
				|| curr_hit_diag - prev_hit_diag > local_wordChunk_diff)
		{
			curr_chunk = make_shared<WordHitsChunk>(curr_wordChunk_id++);
			wordhitschunks.push_back(curr_chunk);
		}

		curr_chunk->wordHitList.push_back(*iter);
		prev_hit_diag = curr_hit_diag;
	}
}

int WordHitsGroup::locate_bridge_within_two_chunks_denovo(WordHitsChunkPtr& head_chunk, WordHitsChunkPtr& tail_chunk, int num_backSearch, const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
	WordHitsChunkBridgePtr bridge_to_be_added;
	int num_bridge_found = 0;

	int local_max_diff = opt.local_wordChunk_diff;
	int best_diff = local_max_diff + 1;
	std::pair<int, int> chunks_backsearch_area_diff = cal_two_wordchunks_backsearch_area_diff(head_chunk, tail_chunk, query, ref_SAIndex, num_backSearch);
	int cleft_and_backsearch_length = tail_chunk->start_pos_in_query - head_chunk->end_pos_in_query - 1 + 2 * num_backSearch;
	long min_bridge_ref_start_pos = head_chunk->end_pos_in_ref - num_backSearch;
	long max_bridge_ref_start_pos = min_bridge_ref_start_pos + cleft_and_backsearch_length;

	for(long curr_bridge_ref_start_pos = min_bridge_ref_start_pos; curr_bridge_ref_start_pos <= max_bridge_ref_start_pos; ++curr_bridge_ref_start_pos)
	{
		long curr_bridge_query_start_pos = head_chunk->end_pos_in_query - num_backSearch + (curr_bridge_ref_start_pos - min_bridge_ref_start_pos);
		if(curr_bridge_query_start_pos + 1 < opt.min_anchor_size || (query.get_length() - curr_bridge_query_start_pos) < opt.min_anchor_size) continue;

		long splice_site_donor_pos = curr_bridge_ref_start_pos + 1;
		long curr_bridge_ref_end_pos = tail_chunk->start_pos_in_ref + num_backSearch - (cleft_and_backsearch_length - (curr_bridge_ref_start_pos - min_bridge_ref_start_pos));
		long splice_site_acceptor_pos = curr_bridge_ref_end_pos - 1;
		cout << splice_site_donor_pos - 1 << ", " << splice_site_acceptor_pos + 1 << endl;

		Strand::Value splice_strand = determin_strand_by_canonical_spliceSite(ref_SAIndex, splice_site_donor_pos, splice_site_acceptor_pos);
		if(splice_strand == Strand::none_decide) continue;
		if(opt.strand_mode & Strand_mode::reverse && splice_strand != head_chunk->strand) continue;
		if(opt.strand_mode & Strand_mode::forward && splice_strand == head_chunk->strand) continue;

		SeqString gap_ref = ref_SAIndex.get_infixSeq(min_bridge_ref_start_pos + 1, curr_bridge_ref_start_pos + 1) + ref_SAIndex.get_infixSeq(curr_bridge_ref_end_pos, tail_chunk->start_pos_in_ref + num_backSearch);
		SeqString gap_query = query.get_infix(head_chunk->end_pos_in_query - num_backSearch + 1, head_chunk->end_pos_in_query - num_backSearch + 1 + cleft_and_backsearch_length);
		GapAndMM gap_mm;
		aln_global(gap_ref, gap_query, gap_mm);
		int adjust_diff = chunks_backsearch_area_diff.first + chunks_backsearch_area_diff.second;
		int diff = gap_mm.total_diff() - adjust_diff;

		if(diff < local_max_diff)
		{
			WordHitsChunkBridgePtr new_bridge = make_shared<WordHitsChunkBridge>();
			new_bridge->head_chunk = head_chunk;
			new_bridge->tail_chunk = tail_chunk;
			new_bridge->start_pos_in_ref = curr_bridge_ref_start_pos;
			new_bridge->end_pos_in_ref = curr_bridge_ref_end_pos;
			new_bridge->start_pos_in_query = curr_bridge_query_start_pos;
			new_bridge->end_pos_in_query = new_bridge->start_pos_in_query + 1;
			new_bridge->gap_mm = gap_mm;
			new_bridge->adjust_diff = adjust_diff;
			new_bridge->sense_strand = splice_strand;
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
