#include "../../../../WordHitsGroupUtil.hpp"
#include <list>

using namespace std;

int main()
{
	WordHitsGroupPtr group = make_shared<WordHitsGroup>(0);

	WordHitsChunkPtr head_chunk = make_shared<WordHitsChunk>(0);
	head_chunk->strand = Strand::forward;
	head_chunk->start_pos_in_ref = 0;
	head_chunk->start_pos_in_query = 1;
	head_chunk->end_pos_in_ref = 5;
	head_chunk->end_pos_in_query = 6;

	WordHitsChunkPtr connect_chunk = make_shared<WordHitsChunk>(1);
	connect_chunk->strand = Strand::forward;
	connect_chunk->start_pos_in_ref = 10;
	connect_chunk->start_pos_in_query = 11;
	connect_chunk->end_pos_in_ref = 15;
	connect_chunk->end_pos_in_query = 16;

	WordHitsChunkPtr tail_chunk = make_shared<WordHitsChunk>(2);
	tail_chunk->strand = Strand::forward;
	tail_chunk->start_pos_in_ref = 20;
	tail_chunk->end_pos_in_ref = 25;
	tail_chunk->start_pos_in_query = 21;
	tail_chunk->end_pos_in_query = 26;

	WordHitsChunkBridgePtr first_bridge = make_shared<WordHitsChunkBridge>(
			head_chunk, connect_chunk,
			5, 10,
			6, 11,
			Strand::forward, 0);

	WordHitsChunkBridgePtr second_bridge = make_shared<WordHitsChunkBridge>(
			connect_chunk, tail_chunk,
			11, 13,
			12, 14,
			Strand::forward, 0);


	/*
	 * head_chunk  connect_chunk
	 * ====..........====.............. 
	 *    └────┬─────┘
	 *    first_bridge
	 *
	 *        connect_chunk      tail_chunk
	 * ..............====..........====
	 *                  └────┬─────┘
	 *                  second_bridge
	 *
	 * ↓
	 *
	 * result:
	 *
	 * head_chunk  connnect_chunk  tail_chunk
	 * ===...........====..........====
	 *   └─────┬─────┘  └────┬─────┘
	 *   first_bridge     second_bridge
	 */

	group->wordhitschunkbridges.push_back(first_bridge);
	group->wordhitschunkbridges.push_back(second_bridge);

	list<WordHitsChunkBridgeChainPtr> result;
	int query_length = 100;
	bool global = false;
	concat_bridges(group->wordhitschunkbridges, result, query_length, global);
	printf("Num of result: %lu\n", result.size());
	for(auto iter = result.begin(); iter != result.end(); ++iter)
	{
		(*iter)->display();
		printf("\n");
	}
}
