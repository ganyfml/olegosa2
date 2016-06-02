// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../../WordHit.hpp"

using namespace std;

int main(int argv, char** argc)
{
	int wordID1 = 1;
	int word1_strand = 1;
	WordHit wordHit1(wordID1, word1_strand);
	wordHit1.ref_pos = atoi(argc[1]);
	WordHitPtr wordHit1ptr = make_shared<WordHit>(wordHit1);

	int wordID2 = 2;
	int word2_strand = 1;
	WordHit wordHit2(wordID2, word2_strand);
	wordHit2.ref_pos = atoi(argc[2]);
	WordHitPtr wordHit2ptr = make_shared<WordHit>(wordHit2);
	
	int wordID3 = 3;
	int word3_strand = 1;
	WordHit wordHit3(wordID3, word3_strand);
	wordHit3.ref_pos = atoi(argc[3]);
	WordHitPtr word3ptr = make_shared<WordHit>(wordHit3);
	
	int wordID4 = 4;
	int word4_strand = 1;
	WordHit wordHit4(wordID4, word4_strand);
	wordHit4.ref_pos = atoi(argc[4]);
	WordHitPtr word4ptr = make_shared<WordHit>(wordHit4);

	list<WordHitPtr> wordptr_list;
	wordptr_list.push_back(wordHit1ptr);	
	wordptr_list.push_back(wordHit2ptr);	
	wordptr_list.push_back(word3ptr);	
	wordptr_list.push_back(word4ptr);	

	cout << is_collinear(wordptr_list) << endl;
}
