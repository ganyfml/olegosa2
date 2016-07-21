// vim: set noexpandtab tabstop=3:

#include <list>
#include "../../../WordHitsGroup.hpp"
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int, char* argv[])
{
	int hit0_wordID = 0;
	WordHit hit0(hit0_wordID);
	hit0.ref_pos = atoi(argv[1]);
	hit0.query_pos= atoi(argv[2]);
	WordHitPtr hit0_ptr = make_shared<WordHit>(hit0);

	int hit1_wordID = 1;
	WordHit hit1(hit1_wordID);
	hit1.ref_pos = atoi(argv[3]);
	hit1.query_pos= atoi(argv[4]);
	WordHitPtr hit1_ptr = make_shared<WordHit>(hit1);

	int group_id = 0;
	WordHitsGroupPtr test_group = make_shared<WordHitsGroup>(group_id);
	test_group->wordhits.push_back(hit0_ptr);
	test_group->wordhits.push_back(hit1_ptr);

	AlnSpliceOpt opt;
	opt.wordChunk_max_diff = 2;
	int num_words = 3;

	test_group->group_wordHits_wordChunks(opt, num_words);

	printf("wordchunk_id\thit_wordIDs\n");
	for(WordHitsChunkPtr chunk: test_group->wordhitschunks)
	{
		printf("%d\t", chunk->id);
		for(WordHitPtr hit: chunk->wordHitList)
		{
			printf("%d, ", hit->word_id);
		}
		printf("\n");
	}
}
