// vim: set noexpandtab tabstop=2:

#include <spliced_aln/WordHitsGroup.hpp>
#include <spliced_aln/WordHitsGroupUtil.hpp>
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

bool can_pair(const WordHitsChunkPtr head_chunk, const WordHitsChunkPtr tail_chunk, const AlnSpliceOpt& opt)
{
	if(!(head_chunk->hit_refPosNonDec) || !(tail_chunk->hit_refPosNonDec)) return false;
	if(head_chunk->gapMM.sum() > opt.wordChunk_max_diff || tail_chunk->gapMM.sum() > opt.wordChunk_max_diff) return false;
	if(head_chunk->strand != tail_chunk->strand) return false;
	if(head_chunk->wordHitList.back()->word_id >= tail_chunk->wordHitList.front()->word_id) return false;
	if(head_chunk->end_pos_in_ref >= tail_chunk->start_pos_in_ref) return false;
	return true;
}

void WordHitsGroup::pair_wordHitsChunks(const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
	for(auto head_chunk_iter = wordhitschunks.begin(); head_chunk_iter != wordhitschunks.end(); ++head_chunk_iter)
	{
		WordHitsChunkPtr head_chunk = *head_chunk_iter;

		for(auto tail_chunk_iter = next(head_chunk_iter); tail_chunk_iter != wordhitschunks.end(); ++tail_chunk_iter)
		{
			WordHitsChunkPtr tail_chunk = *tail_chunk_iter;
			if(!can_pair(head_chunk, tail_chunk, opt))
			{
				continue;
			}

			/***************** If annotation exist, use annotation search first ***************/
			/* For annotation search
			 *          int wordID_diff = tail_chunk->get_wordList().front()->id - head_chunk->get_wordList().back()->id;
			 *                   int gap_length = tail_chunk->start_pos_in_query - head_chunk->end_pos_in_query - 1;
			 *                            */

			locate_bridge_two_chunks(head_chunk, tail_chunk, wordhitschunkbridges, query, ref_SAIndex, opt);
		}
	}
}
