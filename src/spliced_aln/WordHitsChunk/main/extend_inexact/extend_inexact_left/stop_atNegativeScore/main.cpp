// vim: set noexpandtab tabstop=3:

#include <iostream>
#include "../../../../WordHitsChunk.hpp"

using namespace std;

int main()
{
	SeqString query = string("TT");
	SeqString ref = string("TG");
	SeqSuffixArray ref_SAIndex(ref);

	int wordHitChunkID = 0;
	WordHitsChunkPtr chunk = make_shared<WordHitsChunk>(wordHitChunkID);
	chunk->start_pos_in_ref = 1;
	chunk->start_pos_in_query = 1;

	bool stop_atNegativeScore = true;
	printf("before extend, ref_pos: %ld, query_pos: %ld\n", chunk->start_pos_in_ref, chunk->start_pos_in_query);
	chunk->extend_inexact_left(query, ref_SAIndex, stop_atNegativeScore);
	printf("after extend, ref_pos: %ld, query_pos: %ld\n", chunk->start_pos_in_ref, chunk->start_pos_in_query);
}
