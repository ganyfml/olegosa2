#include "../../../../WordHitsGroupUtil.hpp"
#include <list>

using namespace std;

int main()
{
	WordHitsGroupPtr group = make_shared<WordHitsGroup>(0);

	WordHitsChunkPtr head_chunk = make_shared<WordHitsChunk>(0);
	head_chunk->strand = Strand::forward;
	head_chunk->start_pos_in_ref = 0;
	head_chunk->end_pos_in_ref = 5;
	head_chunk->start_pos_in_query = 1;
	head_chunk->end_pos_in_query = 6;
	head_chunk->gapMM.num_mismatch = 6;
	head_chunk->gapMM.num_gapOpenRef = 1;
	head_chunk->gapMM.num_gapExtRef = 2;
	head_chunk->gapMM.num_gapOpenQuery = 3;
	head_chunk->gapMM.num_gapExtQuery = 4;

	WordHitsChunkPtr tail_chunk1 = make_shared<WordHitsChunk>(1);
	tail_chunk1->strand = Strand::forward;
	tail_chunk1->start_pos_in_ref = 10;
	tail_chunk1->end_pos_in_ref = 15;
	tail_chunk1->start_pos_in_query = 11;
	tail_chunk1->end_pos_in_query = 16;
	tail_chunk1->gapMM.num_mismatch = 5;
	tail_chunk1->gapMM.num_gapOpenRef = 1;
	tail_chunk1->gapMM.num_gapExtRef = 2;
	tail_chunk1->gapMM.num_gapOpenQuery = 3;
	tail_chunk1->gapMM.num_gapExtQuery = 4;

	WordHitsChunkPtr tail_chunk2 = make_shared<WordHitsChunk>(2);
	tail_chunk2->strand = Strand::forward;
	tail_chunk2->start_pos_in_ref = 20;
	tail_chunk2->end_pos_in_ref = 25;
	tail_chunk2->start_pos_in_query = 21;
	tail_chunk2->end_pos_in_query = 26;
	tail_chunk2->gapMM.num_mismatch = 5;
	tail_chunk2->gapMM.num_gapOpenRef = 1;
	tail_chunk2->gapMM.num_gapExtRef = 2;
	tail_chunk2->gapMM.num_gapOpenQuery = 3;
	tail_chunk2->gapMM.num_gapExtQuery = 4;

	WordHitsChunkBridgePtr first_bridge = make_shared<WordHitsChunkBridge>(
			head_chunk, tail_chunk1,
			5, 10,
			6, 11,
			Strand::forward, 1);

	WordHitsChunkBridgePtr second_bridge = make_shared<WordHitsChunkBridge>(
			head_chunk, tail_chunk2,
			11, 13,
			12, 14,
			Strand::forward, 1);

	/*
	 * head_chunk   tail_chunk1
	 * ====............====.............. 
	 *    └─────┬──────┘
	 *    first_bridge
	 *
	 * connect_chunk   tail_chunk2
	 * ====..............====
	 *   └───────┬───────┘
	 *    second_bridge
	 *
	 * ↓
	 *
	 * result 1:
	 *
	 * head_chunk   tail_chunk1
	 * ====............====..............
	 *    └─────┬──────┘
	 *    first_bridge
	 *
	 * result 2:
	 *
	 * connect_chunk   tail_chunk2
	 * ====..............====
	 *   └───────┬───────┘
	 *    second_bridge*
	 *
	 */

	group->wordhitschunkbridges.push_back(first_bridge);
	group->wordhitschunkbridges.push_back(second_bridge);

	list<WordHitsChunkBridgeChainPtr> results;
	int query_length = 100;
	bool global = false;
	concat_bridges(group->wordhitschunkbridges, results, query_length, global);
	printf("Num of results: %lu\n", results.size());
	for(auto iter = results.begin(); iter != results.end(); ++iter)
	{
		(*iter)->display();
		printf("\n");
	}
}
