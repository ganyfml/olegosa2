// vim: set noexpandtab tabstop=2:

#include "../../SplicedAlnResult.hpp"
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
	SplicedAlnResultPtr first = make_shared<SplicedAlnResult>();
	WordHitsChunkBridgePtr first_bridge = make_shared<WordHitsChunkBridge>();
	first_bridge->start_pos_in_ref = atoi(argv[1]);
	first_bridge->end_pos_in_ref = atoi(argv[3]);
	WordHitsChunkPtr first_chunk = make_shared<WordHitsChunk>(0);
	first_chunk->strand = static_cast<Strand::Value>(atoi(argv[5]));
	first_bridge->head_chunk = first_chunk;
	first->bridges.push_back(first_bridge);

	SplicedAlnResultPtr second = make_shared<SplicedAlnResult>();
	WordHitsChunkBridgePtr second_bridge = make_shared<WordHitsChunkBridge>();
	second_bridge->start_pos_in_ref = atoi(argv[2]);
	second_bridge->end_pos_in_ref = atoi(argv[4]);
	WordHitsChunkPtr second_chunk = make_shared<WordHitsChunk>(1);
	second_chunk->strand = static_cast<Strand::Value>(atoi(argv[6]));
	second_bridge->head_chunk = second_chunk;
	second->bridges.push_back(second_bridge);

	cout << is_identical(first, second) << endl;
}
