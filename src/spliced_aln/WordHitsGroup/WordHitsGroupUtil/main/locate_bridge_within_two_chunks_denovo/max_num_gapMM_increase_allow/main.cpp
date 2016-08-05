// vim: set noexpandtab tabstop=2:

#include "../../../WordHitsGroupUtil.hpp"
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
	AlnSpliceOpt opt;
	opt.min_intron_size = 1;
	opt.min_anchor_size = 1;

	SeqString query = string(argv[1]);
	SeqString ref = string(argv[2]);
	SeqSuffixArray ref_SAIndex(ref);

	WordHitsGroup wordhit_group = WordHitsGroup(0);

	WordHitsChunkPtr head_chunk = make_shared<WordHitsChunk>(0);
	head_chunk->end_pos_in_ref = atoi(argv[3]);
	head_chunk->end_pos_in_query = atoi(argv[4]);
	wordhit_group.wordhitschunks.push_back(head_chunk);

	WordHitsChunkPtr tail_chunk = make_shared<WordHitsChunk>(1);
	tail_chunk->start_pos_in_ref = atoi(argv[5]);
	tail_chunk->start_pos_in_query = atoi(argv[6]);
	wordhit_group.wordhitschunks.push_back(tail_chunk);

	int num_backSearch = atoi(argv[7]);

	locate_bridge_within_two_chunks_denovo(
			head_chunk, tail_chunk
			, wordhit_group.wordhitschunkbridges
			, num_backSearch
			, query, ref_SAIndex, opt);

	printf("number of bridge created: %lu\n", wordhit_group.wordhitschunkbridges.size());
	if(wordhit_group.wordhitschunkbridges.size() != 0)
	{
		printf("bridge info:\n");
		wordhit_group.wordhitschunkbridges.front()->display();
	}
}
