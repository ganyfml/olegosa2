// vim: set noexpandtab tabstop=2:

#include <spliced_aln/WordHitsGroup.hpp>
#include <vector>

using namespace std;

bool compare_wordHitsGroupByScore(const WordHitsGroupPtr group1, const WordHitsGroupPtr group2)
{
	return group1->score < group2->score;
}

void WordHitsGroup::group_wordHits_wordChunks(const AlnSpliceOpt& opt, int num_words)
{
	vector<int> words_occ(num_words);
	for (auto iter = wordhits.begin(); iter != wordhits.end(); ++iter)
	{
		++words_occ[(*iter)->word_id];
	}

	long prev_hit_diag = -1;
	int local_wordChunk_diff = (opt.wordChunk_max_diff > 2) ? 2 : opt.wordChunk_max_diff;

	int curr_wordChunk_id = 0;
	WordHitsChunkPtr curr_chunk;
	for (auto iter = wordhits.begin(); iter != wordhits.end(); ++iter)
	{
		if(words_occ[(*iter)->word_id] > 1)
			continue;

		long curr_hit_diag = (*iter)->ref_pos - (*iter)->query_pos;
		if (prev_hit_diag == -1
				|| curr_hit_diag - prev_hit_diag > local_wordChunk_diff)
		{
			curr_chunk = make_shared<WordHitsChunk>(curr_wordChunk_id++);
			wordhitschunks.push_back(curr_chunk);
		}

		curr_chunk->wordHitList.push_back(*iter);
		prev_hit_diag = curr_hit_diag;
	}
}
