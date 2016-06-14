// vim: set noexpandtab tabstop=3:

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
