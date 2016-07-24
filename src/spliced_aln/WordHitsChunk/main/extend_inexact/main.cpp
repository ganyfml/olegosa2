// vim: set noexpandtab tabstop=3:

#include <iostream>
#include "../../WordHitsChunk.hpp"

using namespace std;

int main()
{
	SeqString query = string("AGT");
	SeqString ref = string(string("AGT"));
	SeqSuffixArray ref_SAIndex(ref);

	int wordHitChunkID = 0;
	WordHitsChunkPtr chunk = make_shared<WordHitsChunk>(wordHitChunkID);
	chunk->refStart_pos = 1;
	chunk->refEnd_pos = 1;
	chunk->queryStart_pos = 1;
	chunk->queryEnd_pos = 1;

	bool stop_atNegativeScore = false;
	printf("Before extend: ref_start: %ld, ref_end: %ld, query_start: %ld, query_end: %ld\n", chunk->refStart_pos, chunk->refEnd_pos, chunk->queryStart_pos, chunk->queryEnd_pos);
	chunk->extend_inexact(query, ref_SAIndex, stop_atNegativeScore, ExtendDirection::both);
	printf("After extend: ref_start: %ld, ref_end: %ld, query_start: %ld, query_end: %ld\n", chunk->refStart_pos, chunk->refEnd_pos, chunk->queryStart_pos, chunk->queryEnd_pos);
}
