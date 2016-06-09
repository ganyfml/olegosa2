// vim: set noexpandtab tabstop=3:

#include <spliced_aln/splicedAlnUtil.hpp>
#include <nonspliced_aln/nonsplicedAln.hpp>
#include <util/AlnResult.hpp>
#include <queue>

using namespace std;

void generate_words(const SeqString& query, std::vector<WordPtr>& words, const AlnSpliceOpt& opt)
{
  int num_words = (query.get_length() - opt.word_max_overlap) / (opt.word_length - opt.word_max_overlap);
  for(int i = 0; i != num_words; ++i)
  {
	 int query_pos = opt.word_length * i + (int(query.get_length()) - num_words * opt.word_length) * i / (num_words - 1);
	 SeqString word_seq = query.get_infix(query_pos, query_pos + opt.word_length);
	 SeqString word_rseq = word_seq.get_revcomp();
	 int rev_query_pos = query.get_length() - (query_pos + opt.word_length);
	 words.push_back(std::make_shared<Word>(i, opt.word_length, query_pos, rev_query_pos, word_seq, word_rseq));	
  }
}

void collect_wordHitsByAlnResult(std::queue<AlnResult>& word_hit_result, std::list<WordHitPtr>& wordHitList, const SeqSuffixArray& ref_SAIndex, WordPtr current_word, int strand)
{
  while(!word_hit_result.empty())
  {
	 AlnResult a = word_hit_result.front();
	 word_hit_result.pop();
	 current_word->num_occ += a.SA_index_high - a.SA_index_low;
	 for(unsigned long i = a.SA_index_low; i < a.SA_index_high; ++i)
	 {
		WordHit w(current_word->id, strand);
		w.query_pos = strand ? current_word->r_query_pos : current_word->query_pos;
		w.ref_pos = ref_SAIndex.SAIndex2SeqPos(i);
		wordHitList.push_front(make_shared<WordHit>(w));
	 }
  }
}

void collect_wordHits(const std::vector<WordPtr>& words, std::list<WordHitPtr>& wordHitList, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
  alnNonspliceOpt word_search_opt;
  for(auto word_iter = words.begin(); word_iter != words.end(); ++word_iter)
  {
	 std::queue<AlnResult> word_hit_result;
	 nonsplicedAln((*word_iter)->seq, word_hit_result, ref_SAIndex, word_search_opt);
	 collect_wordHitsByAlnResult(word_hit_result, wordHitList, ref_SAIndex, *word_iter, 0);
	 nonsplicedAln((*word_iter)->r_seq, word_hit_result, ref_SAIndex, word_search_opt);
	 collect_wordHitsByAlnResult(word_hit_result, wordHitList, ref_SAIndex, *word_iter, 2);
  }
}

void group_wordHits_wordHitsGroup(const list<WordHitPtr>& hits, list<WordHitsGroupPtr>& groups, int max_intron_size)
{
  long prev_ref_pos = -1;
  int prev_strand = -1;
  int prev_word_direction = 0;
  int prev_wordID = -1;

  int curr_wordGroup_id = 0;
  WordHitsGroupPtr curr_group;
  for (auto iter = hits.begin(); iter != hits.end(); ++iter)
  {
	 WordHitPtr hit = *iter;
	 long curr_wordID = hit->word_id;
	 int curr_word_direction = 0;
	 long curr_ref_pos = hit->ref_pos;

	 if(prev_wordID != -1)
	 {
		int wordID_diff = curr_wordID - prev_wordID;
		if (wordID_diff != 0)
		{
		  curr_word_direction = abs(wordID_diff) / wordID_diff;
		}
		else
		{
		  curr_word_direction = 2;
		}
	 }

	 if (hit->strand != prev_strand
		  || curr_ref_pos - prev_ref_pos > 2 * max_intron_size
		  || curr_word_direction == 2
		  || (prev_word_direction != 0 && prev_word_direction != curr_word_direction))
	 {
		prev_wordID = -1;
		curr_word_direction = 0;
		curr_group = make_shared<WordHitsGroup>(curr_wordGroup_id++);
		groups.push_back(curr_group);
	 }

	 curr_group->wordhits.push_back(hit);
	 prev_word_direction = curr_word_direction;
	 prev_ref_pos = curr_ref_pos;
	 prev_wordID = curr_wordID;
	 prev_strand = hit->strand;
  }
}
