// vim: set noexpandtab tabstop=3:

#include <iostream>
#include "../../../../WordHitsChunk.hpp"

using namespace std;

int main()
{
	SeqString query = string("TT");
	SeqString ref = string(string("TG"));
	SeqSuffixArray ref_SAIndex(ref);

	int wordHitChunkID = 0;
	WordHitsChunkPtr chunk = make_shared<WordHitsChunk>(wordHitChunkID);
	chunk->refStart_pos = 1;
	chunk->queryStart_pos = 1;

	bool stop_atNegativeScore = true;
	printf("before extend, ref_pos: %ld, query_pos: %ld\n", chunk->refStart_pos, chunk->queryStart_pos);
	chunk->extend_inexact_left(query, ref_SAIndex, stop_atNegativeScore);
	printf("aftern extend, ref_pos: %ld, query_pos: %ld\n", chunk->refStart_pos, chunk->queryStart_pos);
}
