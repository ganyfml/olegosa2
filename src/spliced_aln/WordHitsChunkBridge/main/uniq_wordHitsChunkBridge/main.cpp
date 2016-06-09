// vim: set noexpandtab tabstop=2:

#include "../../WordHitsChunkBridge.hpp"
#include <vector>

using namespace std;

int main(int, char* argv[])
{
	vector<WordHitsChunkPtr> chunks;
	WordHitsChunkPtr chunk1 = make_shared<WordHitsChunk>(0);
	WordHitsChunkPtr chunk2 = make_shared<WordHitsChunk>(1);
	WordHitsChunkPtr chunk3 = make_shared<WordHitsChunk>(2);
	chunks.push_back(chunk1);
	chunks.push_back(chunk2);
	chunks.push_back(chunk3);

	WordHitsChunkBridgePtr bridge1 = make_shared<WordHitsChunkBridge>();
	bridge1->head_chunk = chunks[atoi(argv[1])];
	bridge1->tail_chunk = chunks[atoi(argv[3])];
	bridge1->refStart_pos = atoi(argv[5]);
	bridge1->refEnd_pos = atoi(argv[7]);

	WordHitsChunkBridgePtr bridge2 = make_shared<WordHitsChunkBridge>();
	bridge2->head_chunk = chunks[atoi(argv[2])];
	bridge2->tail_chunk = chunks[atoi(argv[4])];
	bridge2->refStart_pos = atoi(argv[6]);
	bridge2->refEnd_pos = atoi(argv[8]);

	list<WordHitsChunkBridgePtr> bridge_list;
	bridge_list.push_back(bridge1);
	bridge_list.push_back(bridge2);

	uniq_wordHitsChunkBridge(bridge_list);
	printf("Num of bridges remians in the list: %lu\n", bridge_list.size());
}
