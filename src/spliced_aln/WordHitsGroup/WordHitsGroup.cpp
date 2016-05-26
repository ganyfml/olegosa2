// vim: set noexpandtab tabstop=2:

#include <cmath>
#include <spliced_aln/WordHitsGroup.hpp>

using namespace std;

void WordHitsGroup::group_wordHits_wordChunks(const AlnSpliceOpt& opt, int num_words)
{
	vector<int> words_occ(num_words);
	for (auto iter = wordhits.begin(); iter != wordhits.end(); ++iter)
	{
		++words_occ[(*iter)->word_id];
	}

	int prev_strand = -1;
	long prev_hit_diag = -1;
	int local_wordChunk_diff = (opt.wordChunk_max_diff > 2) ? 2 : opt.wordChunk_max_diff;

	int curr_wordChunk_id = 0;
	WordHitsChunkPtr curr_chunk;
	for (auto iter = wordhits.begin(); iter != wordhits.end(); ++iter)
	{
		if(words_occ[(*iter)->word_id] > 1)
			continue;

		long curr_hit_diag = (*iter)->ref_pos - (*iter)->query_pos;
		if ((*iter)->strand != prev_strand || curr_hit_diag - prev_hit_diag > local_wordChunk_diff)
		{
			curr_chunk = make_shared<WordHitsChunk>(curr_wordChunk_id++);
			wordhitschunks.push_back(curr_chunk);
		}

		curr_chunk->wordHitList.push_back(*iter);
		prev_hit_diag = curr_hit_diag;
		prev_strand = (*iter)->strand;
	}
}

double calculate_wordhitsChunk_score(const WordHitsGroupPtr& group, const vector<WordPtr>& words, long ref_length, int num_words)
{
  double log_occ = 0;
	bool word_uniqueness[num_words];
  int num_wordHits_uniq = 0;

  for (auto iter = group->wordhits.begin(); iter != group->wordhits.end(); ++iter)
	{
    int word_id = (*iter)->word_id;
    if (word_uniqueness[word_id])
			continue;

		word_uniqueness[word_id] = true;
    ++num_wordHits_uniq;
    log_occ += log10((double)words[word_id]->num_occ);
  }
  return log_occ - (num_wordHits_uniq - 1) * log10((double)ref_length);
}
