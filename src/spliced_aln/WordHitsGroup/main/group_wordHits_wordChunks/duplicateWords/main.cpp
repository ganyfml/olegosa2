// vim: set noexpandtab tabstop=3:

#include <list>
#include "../../../WordHitsGroup.hpp"
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int, char* argv[])
{
  int hit1_wordid = atoi(argv[1]);
  WordHit hit1(hit1_wordid);
  hit1.ref_pos = 2;
  hit1.query_pos= 1;
  WordHitPtr hit1_ptr = make_shared<WordHit>(hit1);

  int hit2_wordid = atoi(argv[2]);
  WordHit hit2(hit2_wordid);
  hit2.ref_pos = 3;
  hit2.query_pos= 2;
  WordHitPtr hit2_ptr = make_shared<WordHit>(hit2);

  int hit3_wordid = atoi(argv[3]);
  WordHit hit3(hit3_wordid);
  hit3.ref_pos = 4;
  hit3.query_pos= 3;
  WordHitPtr hit3_ptr = make_shared<WordHit>(hit3);

  int group_id = 0;
  WordHitsGroupPtr test_chunk = make_shared<WordHitsGroup>(group_id);
  test_chunk->wordhits.push_back(hit1_ptr);
  test_chunk->wordhits.push_back(hit2_ptr);
  test_chunk->wordhits.push_back(hit3_ptr);

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
