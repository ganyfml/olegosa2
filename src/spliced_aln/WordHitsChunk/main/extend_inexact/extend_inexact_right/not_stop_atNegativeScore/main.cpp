// vim: set noexpandtab tabstop=3:

#include <iostream>
#include "../../../../WordHitsChunk.hpp"

using namespace std;

int main()
{
	SeqString query = string("TT");
	SeqString ref = string("GT");
	SeqSuffixArray ref_SAIndex(ref);

	int wordHitChunkID = 0;
	WordHitsChunkPtr chunk = make_shared<WordHitsChunk>(wordHitChunkID);
	chunk->end_pos_in_ref = 0;
	chunk->end_pos_in_query = 0;

	bool stop_atNegativeScore = false;
	printf("before extend, ref_pos: %ld, query_pos: %d\n", chunk->end_pos_in_ref, chunk->end_pos_in_query);
	chunk->extend_inexact_right(query, ref_SAIndex, stop_atNegativeScore);
	printf("after extend, ref_pos: %ld, query_pos: %d\n", chunk->end_pos_in_ref, chunk->end_pos_in_query);
}
