// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../../WordHit.hpp"

using namespace std;

int main(int argv, char** argc)
{
	int wordID1 = 1;
	int word1Strand = 0;
	WordHit wordHit1 (wordID1, word1Strand);
	wordHit1.ref_pos = atoi(argc[1]);
	wordHit1.query_pos = atoi(argc[2]);
	WordHitPtr wordHit1ptr = make_shared<WordHit>(wordHit1);

	int wordID2 = 2;
	int word2Strand = 0;
	WordHit wordHit2 (wordID2, word2Strand);
	wordHit2.ref_pos = atoi(argc[3]);
	wordHit2.query_pos = atoi(argc[4]);
	WordHitPtr wordHit2ptr = make_shared<WordHit>(wordHit2);
	
	wordHit1ptr->display();
	wordHit2ptr->display();
	cout << endl << "Result: " << compare_wordHitsByHitDiagonal(wordHit1ptr, wordHit2ptr) << endl;
}