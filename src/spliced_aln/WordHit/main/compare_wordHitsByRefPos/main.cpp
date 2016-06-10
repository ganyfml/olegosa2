// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../../WordHit.hpp"

using namespace std;

int main(int, char** argc)
{
	int wordID1 = 1;
	int word1_strand = 0;
	WordHit wordHit1(wordID1, word1_strand);
	wordHit1.ref_pos = atoi(argc[1]);
	WordHitPtr wordHit1ptr = make_shared<WordHit>(wordHit1);

	int wordID2 = 2;
	int word2_strand = 0;
	WordHit wordHit2(wordID2, word2_strand);
	wordHit2.ref_pos = atoi(argc[2]);
	WordHitPtr wordHit2ptr = make_shared<WordHit>(wordHit2);

	printf("word 1 ref pos: %lu\n", wordHit1ptr->ref_pos);
	printf("word 2 ref pos: %lu\n", wordHit2ptr->ref_pos);
	cout << endl << "Result: " << compare_wordHitsByRefPos(wordHit1ptr, wordHit2ptr) << endl;
}
