// vim: set noexpandtab tabstop=2:

#include "../../../../../SplicedAlnResult.hpp"
#include <iostream>

using namespace std;

int main()
{
	SplicedAlnResultPtr test_result = make_shared<SplicedAlnResult>();

	WordHitsChunkBridgePtr test_bridge = make_shared<WordHitsChunkBridge>();
	test_bridge->sense_strand = 9;
	test_bridge->score = 10;
	test_bridge->adjust_diff = 2;

	WordHitsChunkPtr head_chunk = make_shared<WordHitsChunk>(0);
	WordHitsChunkPtr tail_chunk = make_shared<WordHitsChunk>(1);

	head_chunk->refStart_pos = 1;
	head_chunk->queryStart_pos = 2;
	head_chunk->strand= 1;

	tail_chunk->refEnd_pos = 3;
	tail_chunk->queryEnd_pos = 4;

	head_chunk->gapMM.num_mismatch = 5;
	head_chunk->gapMM.num_gapOpenRef = 1;
	head_chunk->gapMM.num_gapExtRef = 2;
	head_chunk->gapMM.num_gapOpenQuery = 3;
	head_chunk->gapMM.num_gapExtQuery = 4;

	tail_chunk->gapMM.num_mismatch = 5;
	tail_chunk->gapMM.num_gapOpenRef = 1;
	tail_chunk->gapMM.num_gapExtRef = 2;
	tail_chunk->gapMM.num_gapOpenQuery = 3;
	tail_chunk->gapMM.num_gapExtQuery = 4;

	test_bridge->gap_mm.num_mismatch = 5;
	test_bridge->gap_mm.num_gapOpenRef = 1;
	test_bridge->gap_mm.num_gapExtRef = 2;
	test_bridge->gap_mm.num_gapOpenQuery = 3;
	test_bridge->gap_mm.num_gapExtQuery = 4;
	test_bridge->head_chunk = head_chunk;
	test_bridge->tail_chunk = tail_chunk;
	
	test_result->bridges.push_back(test_bridge);
	test_result->evaluate(true, 100);
	test_result->display();
}
