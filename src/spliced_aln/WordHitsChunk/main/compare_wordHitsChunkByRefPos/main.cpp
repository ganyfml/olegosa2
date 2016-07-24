// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../../WordHitsChunk.hpp"

using namespace std;

int main(int, char* argv[])
{
	int chunk1_id = 0;
	WordHitsChunkPtr chunk1 = make_shared<WordHitsChunk>(chunk1_id);
	chunk1->hit_refPosNonDec = bool(atoi(argv[1]));
	chunk1->start_pos_in_ref = atoi(argv[2]);

	int chunk2_id = 0;
	WordHitsChunkPtr chunk2 = make_shared<WordHitsChunk>(chunk2_id);
	chunk2->hit_refPosNonDec = bool(atoi(argv[3]));
	chunk2->start_pos_in_ref = atoi(argv[4]);

	printf("%d\n", compare_wordHitsChunkByRefPos(chunk1, chunk2));
}
