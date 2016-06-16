// vim: set noexpandtab tabstop=3:

#include <list>
#include "../../../WordHitsGroup.hpp"
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int argc, char* argv[])
{
  int group_id = 0;
  WordHitsGroupPtr test_group = make_shared<WordHitsGroup>(group_id);
  for(int i = 0; i < argc - 1; ++i)
  {
	 int hit_wordID = atoi(argv[i+1]);
	 WordHitPtr hit = make_shared<WordHit>(hit_wordID);
	 hit->ref_pos = i + 1;
	 hit->query_pos= i;
	 test_group->wordhits.push_back(hit);
  }

  AlnSpliceOpt opt;
  opt.wordChunk_max_diff = 100;

  int num_words = 3;
  test_group->group_wordHits_wordChunks(opt, num_words);

  printf("wordchunk_id\thit_wordIDs\n");
  for(WordHitsChunkPtr chunk : test_group->wordhitschunks)
  {
	 printf("%d\t", chunk->id);
	 for(WordHitPtr hit : chunk->wordHitList)
	 {
		printf("%d, ", hit->word_id);
	 }
	 printf("\n");
  }
}
