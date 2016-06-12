// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../WordHit.hpp"

using namespace std;

int main()
{
	int wordID1 = 1;
	WordHitPtr wordHit1 = make_shared<WordHit>(wordID1);
	wordHit1->ref_pos = 2;
	wordHit1->query_pos = 3;
	wordHit1->display();
}
