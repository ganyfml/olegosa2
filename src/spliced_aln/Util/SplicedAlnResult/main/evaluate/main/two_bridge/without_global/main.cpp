// vim: set noexpandtab tabstop=2:

#include "../../../../../SplicedAlnResult.hpp"
#include <iostream>

using namespace std;

int main()
{
	SplicedAlnResultPtr test_result = make_shared<SplicedAlnResult>();

	WordHitsChunkBridgePtr test_bridge1 = make_shared<WordHitsChunkBridge>();
	test_bridge1->sense_strand = 9;
	test_bridge1->score = 10;
	test_bridge1->adjust_diff = 2;

	WordHitsChunkPtr bridge1_head_chunk = make_shared<WordHitsChunk>(0);
	WordHitsChunkPtr bridge1_tail_chunk = make_shared<WordHitsChunk>(1);
	bridge1_head_chunk->refStart_pos = 1;
	bridge1_head_chunk->queryStart_pos = 2;
	bridge1_head_chunk->strand= 1;

	bridge1_head_chunk->gapMM.num_mismatch = 5;
	bridge1_head_chunk->gapMM.num_gapOpenRef = 1;
	bridge1_head_chunk->gapMM.num_gapExtRef = 2;
	bridge1_head_chunk->gapMM.num_gapOpenQuery = 3;
	bridge1_head_chunk->gapMM.num_gapExtQuery = 4;

	bridge1_tail_chunk->gapMM.num_mismatch = 5;
	bridge1_tail_chunk->gapMM.num_gapOpenRef = 1;
	bridge1_tail_chunk->gapMM.num_gapExtRef = 2;
	bridge1_tail_chunk->gapMM.num_gapOpenQuery = 3;
	bridge1_tail_chunk->gapMM.num_gapExtQuery = 4;

	test_bridge1->gap_mm.num_mismatch = 5;
	test_bridge1->gap_mm.num_gapOpenRef = 1;
	test_bridge1->gap_mm.num_gapExtRef = 2;
	test_bridge1->gap_mm.num_gapOpenQuery = 3;
	test_bridge1->gap_mm.num_gapExtQuery = 4;
	test_bridge1->head_chunk = bridge1_head_chunk;
	test_bridge1->tail_chunk = bridge1_tail_chunk;
	
	WordHitsChunkBridgePtr test_bridge2 = make_shared<WordHitsChunkBridge>();
	test_bridge2->score = 20;
	test_bridge2->adjust_diff = 3;

	WordHitsChunkPtr bridge2_tail_chunk = make_shared<WordHitsChunk>(3);
	bridge2_tail_chunk->refEnd_pos = 3;
	bridge2_tail_chunk->queryEnd_pos = 4;

	bridge2_tail_chunk->gapMM.num_mismatch = 5;
	bridge2_tail_chunk->gapMM.num_gapOpenRef = 1;
	bridge2_tail_chunk->gapMM.num_gapExtRef = 2;
	bridge2_tail_chunk->gapMM.num_gapOpenQuery = 3;
	bridge2_tail_chunk->gapMM.num_gapExtQuery = 4;

	test_bridge2->gap_mm.num_mismatch = 5;
	test_bridge2->gap_mm.num_gapOpenRef = 1;
	test_bridge2->gap_mm.num_gapExtRef = 2;
	test_bridge2->gap_mm.num_gapOpenQuery = 3;
	test_bridge2->gap_mm.num_gapExtQuery = 4;
	test_bridge2->tail_chunk = bridge2_tail_chunk;

	test_result->bridges.push_back(test_bridge1);
	test_result->bridges.push_back(test_bridge2);
	test_result->evaluate(false, 1000);
	test_result->display();
}
