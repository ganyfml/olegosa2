// vim: set noexpandtab tabstop=3:

#include <list>
#include "../../../WordHitsGroup.hpp"
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int argc, char* argv[])
{
  int hit1_id = 1;
  int hit1_strand = 0;
  WordHit hit1(hit1_id, hit1_strand);
  hit1.ref_pos = atoi(argv[1]);
  hit1.query_pos= atoi(argv[2]);
  WordHitPtr hit1_ptr = make_shared<WordHit>(hit1);

  int hit2_id = 2;
  int hit2_strand = 0;
  WordHit hit2(hit2_id, hit2_strand);
  hit2.ref_pos = atoi(argv[3]);
  hit2.query_pos= atoi(argv[4]);
  WordHitPtr hit2_ptr = make_shared<WordHit>(hit2);

  int group_id = 0;
  WordHitsGroupPtr test_chunk = make_shared<WordHitsGroup>(group_id);
  test_chunk->wordhits.push_back(hit1_ptr);
  test_chunk->wordhits.push_back(hit2_ptr);

  AlnSpliceOpt opt;
  opt.wordChunk_max_diff = 2;
  int num_words = 3;

  test_chunk->group_wordHits_wordChunks(opt, num_words);

  for(auto iter = test_chunk->wordhitschunks.begin(); iter != test_chunk->wordhitschunks.end(); ++iter)
  {
	 (*iter)->display();
	 printf("\n");
  }
}
