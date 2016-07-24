// vim: set noexpandtab tabstop=3:

#include <iostream>
#include "../../../../WordHitsChunk.hpp"

using namespace std;

int main()
{
	SeqString query = string("TT");
	SeqString ref = string(string("GT"));
	SeqSuffixArray ref_SAIndex(ref);

	int wordHitChunkID = 0;
	WordHitsChunkPtr chunk = make_shared<WordHitsChunk>(wordHitChunkID);
	chunk->refEnd_pos = 0;
	chunk->queryEnd_pos = 0;

	bool stop_atNegativeScore = true;
	printf("before extend, ref_pos: %ld, query_pos: %ld\n", chunk->refEnd_pos, chunk->queryEnd_pos);
	chunk->extend_inexact_right(query, ref_SAIndex, stop_atNegativeScore);
	printf("aftern extend, ref_pos: %ld, query_pos: %ld\n", chunk->refEnd_pos, chunk->queryEnd_pos);
}
