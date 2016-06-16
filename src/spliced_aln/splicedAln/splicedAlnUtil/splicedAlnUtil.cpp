// vim: set noexpandtab tabstop=2:

#include <spliced_aln/splicedAlnUtil.hpp>
#include <nonspliced_aln/nonsplicedAln.hpp>
#include <util/AlnResult.hpp>
#include <queue>

using namespace std;

void generate_words(const SeqString& query, std::vector<WordPtr>& words, const AlnSpliceOpt& opt)
{
	int num_words = (query.get_length() - opt.word_max_overlap) / (opt.word_length - opt.word_max_overlap);
	if(num_words >= 2)
	{
		for(int i = 0; i < num_words; ++i)
		{
			int query_pos = opt.word_length * i + (int(query.get_length()) - num_words * opt.word_length) * i / (num_words - 1);
			SeqString word_seq = query.get_infix(query_pos, query_pos + opt.word_length);
			int rev_query_pos = query.get_length() - (query_pos + opt.word_length);
			words.push_back(std::make_shared<Word>(i, query_pos, rev_query_pos, word_seq));	
		}
	}
}

void collect_wordHits(const std::vector<WordPtr>& words, std::list<WordHitPtr>& wordHitList, const SeqSuffixArray& ref_SAIndex, bool revcomp, const alnNonspliceOpt& word_search_opt)
{
	for(auto word_iter = words.begin(); word_iter != words.end(); ++word_iter)
	{
		std::queue<AlnResult> word_hit_result;
		nonsplicedAln((*word_iter)->seq, word_hit_result, ref_SAIndex, word_search_opt);
		while(!word_hit_result.empty())
		{
			AlnResult a = word_hit_result.front();
			word_hit_result.pop();
			(*word_iter)->num_occ += a.SA_index_high - a.SA_index_low;
			for(unsigned long i = a.SA_index_low; i < a.SA_index_high; ++i)
			{
				WordHit w((*word_iter)->id);
				w.query_pos = revcomp ? (*word_iter)->r_query_pos : (*word_iter)->query_pos;
				w.ref_pos = ref_SAIndex.SAIndex2SeqPos(i);
				wordHitList.push_front(make_shared<WordHit>(w));
			}
		}
	}
}

int sign(int x)
{
	return (x > 0) - (x < 0);
}

void group_wordHits_wordHitsGroup(const list<WordHitPtr>& hits, list<WordHitsGroupPtr>& groups, int max_hits_dist_within_group)
{
	auto prev_hit_iter = hits.begin();
	auto curr_hit_iter = ++hits.begin();

	int curr_wordGroup_id = 0;
	WordHitsGroupPtr curr_group = make_shared<WordHitsGroup>(curr_wordGroup_id++);
	groups.push_back(curr_group);
	curr_group->wordhits.push_back(*prev_hit_iter);

	bool first_hit_in_curr_group = true;
	int prev_word_direction = 0;

	while(curr_hit_iter != hits.end())
	{
		int curr_word_direction = sign((*prev_hit_iter)->word_id - (*curr_hit_iter)->word_id);

		if(((*curr_hit_iter)->ref_pos - (*prev_hit_iter)->ref_pos > max_hits_dist_within_group) //max_hits_dist_within_group = 2 * max_intro_size
				|| curr_word_direction == 0
				|| (!first_hit_in_curr_group && curr_word_direction != prev_word_direction))
		{
			curr_group = make_shared<WordHitsGroup>(curr_wordGroup_id++);
			groups.push_back(curr_group);
			first_hit_in_curr_group = true;
		}
		else
		{
			first_hit_in_curr_group = false;
			prev_word_direction = curr_word_direction;
		}
		curr_group->wordhits.push_back(*curr_hit_iter);
		++prev_hit_iter;
		++curr_hit_iter;
	}
}
