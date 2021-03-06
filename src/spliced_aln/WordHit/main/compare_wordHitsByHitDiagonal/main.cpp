// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../../WordHit.hpp"

using namespace std;

int main(int, char** argc)
{
	int wordID1 = 1;
	WordHit wordHit1 (wordID1);
	wordHit1.ref_pos = atoi(argc[1]);
	wordHit1.query_pos = atoi(argc[2]);
	WordHitPtr wordHit1ptr = make_shared<WordHit>(wordHit1);

	int wordID2 = 2;
	WordHit wordHit2 (wordID2);
	wordHit2.ref_pos = atoi(argc[3]);
	wordHit2.query_pos = atoi(argc[4]);
	WordHitPtr wordHit2ptr = make_shared<WordHit>(wordHit2);

	printf("word 1 hit diagona: %lu\n", wordHit1ptr->ref_pos - wordHit1ptr->query_pos);
	printf("word 2 hit diagona: %lu\n", wordHit2ptr->ref_pos - wordHit2ptr->query_pos);
	cout << endl << "Result: " << compare_wordHitsByHitDiagonal(wordHit1ptr, wordHit2ptr) << endl;
}
