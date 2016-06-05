// vim: set noexpandtab tabstop=2:

#include "../../WordHitsChunkBridge.hpp"

using namespace std;

int main(int, char* argv[])
{
	WordHitsChunkBridgePtr bridge1 = make_shared<WordHitsChunkBridge>();
	WordHitsChunk b1_chunk = make_shared<WordHitsChunk>(0);
	b1_chunk->strand = atoi(agrv[1]);
	bridge1->sense_strand = 0;
	b1_chunk->refStart_pos = 0;

	WordHitsChunkBridgePtr bridge2 = make_shared<WordHitsChunkBridge>();
	WordHitsChunk b1_chunk = make_shared<WordHitsChunk>(1);
	b2_chunk->strand = atoi(agrv[2]);
	bridge2->sense_strand = atoi(argv[4])
	b2_chunk->refStart_pos = atoi(agrv[6]);
}
