// vim: set noexpandtab tabstop=3:

#include <spliced_aln/splicedAlnUtil.hpp>
#include <nonspliced_aln/nonsplicedAln.hpp>
#include <util/AlnResult.hpp>
#include <queue>

using namespace std;

void generate_words(const SeqString& query, std::vector<WordPtr>& words, const AlnSpliceOpt& opt)
{
  int num_words = (query.get_length() - opt.word_max_overlap) / (opt.word_length - opt.word_max_overlap);
  if(num_words < 2) return;
  else
  {
	 for(int i = 0; i != num_words; ++i)
	 {
		int query_pos = opt.word_length * i + (int(query.get_length()) - num_words * opt.word_length) * i / (num_words - 1);
		SeqString word_seq = query.get_infix(query_pos, query_pos + opt.word_length);
		SeqString word_rseq = word_seq.get_revcomp();
		int rev_query_pos = query.get_length() - (query_pos + opt.word_length);
		words.push_back(std::make_shared<Word>(i, opt.word_length, query_pos, rev_query_pos, word_seq, word_rseq));	
	 }
  }
}
