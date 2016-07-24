// vim: set noexpandtab tabstop=3:

#include <iostream>
#include "../../WordHitsChunk.hpp"

using namespace std;

int main()
{
	SeqString query = string("AGT");
	SeqString ref = string("AGT");
	SeqSuffixArray ref_SAIndex(ref);

	int wordHitChunkID = 0;
	WordHitsChunkPtr chunk = make_shared<WordHitsChunk>(wordHitChunkID);
	chunk->start_pos_in_ref = 1;
	chunk->end_pos_in_ref = 1;
	chunk->start_pos_in_query = 1;
	chunk->end_pos_in_query = 1;

	bool stop_atNegativeScore = false;
	printf("Before extend: ref_start: %ld, ref_end: %ld, query_start: %ld, query_end: %ld\n", chunk->start_pos_in_ref, chunk->end_pos_in_ref, chunk->start_pos_in_query, chunk->end_pos_in_query);
	chunk->extend_inexact(query, ref_SAIndex, stop_atNegativeScore, ExtendDirection::both);
	printf("After extend: ref_start: %ld, ref_end: %ld, query_start: %ld, query_end: %ld\n", chunk->start_pos_in_ref, chunk->end_pos_in_ref, chunk->start_pos_in_query, chunk->end_pos_in_query);
}
