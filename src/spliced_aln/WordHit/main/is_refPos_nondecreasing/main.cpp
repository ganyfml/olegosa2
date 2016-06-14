// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <list>
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

	list<WordHitPtr> wordptr_list;
	wordptr_list.push_back(wordHit1ptr);	
	wordptr_list.push_back(wordHit2ptr);	

	cout << is_refPos_nondecreasing(wordptr_list) << endl;
}
