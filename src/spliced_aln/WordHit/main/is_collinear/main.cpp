// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../../WordHit.hpp"

using namespace std;

int main(int, char** argc)
{
	int wordID1 = 1;
	WordHit wordHit1(wordID1);
	wordHit1.ref_pos = atoi(argc[1]);
	WordHitPtr wordHit1ptr = make_shared<WordHit>(wordHit1);

	int wordID2 = 2;
	WordHit wordHit2(wordID2);
	wordHit2.ref_pos = atoi(argc[2]);
	WordHitPtr wordHit2ptr = make_shared<WordHit>(wordHit2);

	int wordID3 = 3;
	WordHit wordHit3(wordID3);
	wordHit3.ref_pos = atoi(argc[3]);
	WordHitPtr word3ptr = make_shared<WordHit>(wordHit3);

	int wordID4 = 4;
	WordHit wordHit4(wordID4);
	wordHit4.ref_pos = atoi(argc[4]);
	WordHitPtr word4ptr = make_shared<WordHit>(wordHit4);

	list<WordHitPtr> wordptr_list;
	wordptr_list.push_back(wordHit1ptr);	
	wordptr_list.push_back(wordHit2ptr);	
	wordptr_list.push_back(word3ptr);	
	wordptr_list.push_back(word4ptr);	

	cout << is_collinear(wordptr_list) << endl;
}
