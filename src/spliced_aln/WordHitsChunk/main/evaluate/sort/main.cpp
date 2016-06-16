// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../../../WordHitsChunk.hpp"

using namespace std;

int main()
{
	int hit1_word_id = 0;
	WordHitPtr hit1 = make_shared<WordHit>(hit1_word_id);
	hit1->ref_pos = 1;
	hit1->query_pos = 2;

	int hit2_word_id = 3;
	WordHitPtr hit2 = make_shared<WordHit>(hit2_word_id);
	hit2->ref_pos = 5;
	hit2->query_pos = 6;

	int chunk1_id = 0;
	WordHitsChunkPtr chunk = make_shared<WordHitsChunk>(chunk1_id);
	chunk->wordHitList.push_back(hit2);
	chunk->wordHitList.push_back(hit1);

	printf("before evaluate: \n");
	chunk->display();
	int word_size = 5;
	int hit_strand = 1;
	chunk->evaluate(word_size, hit_strand);
	printf("\nAfter evaluate: \n");
	chunk->display();
}
