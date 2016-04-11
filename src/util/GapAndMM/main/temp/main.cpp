// vim: set noexpandtab tabstop=2:

#include <util/GapAndMM.hpp>
#include <iostream>
#include <queue>

using namespace std;

int main()
{
	GapAndMM test1;
	test1.num_mismatch = 1;
	test1.num_gapOpenRef = 2;
	test1.num_gapExtRef = 3;
	test1.num_gapOpenQuery = 4;
	test1.num_gapExtQuery = 5;

	test1.display();

	queue<GapAndMM> q;
	q.emplace(test1);
	GapAndMM test2 = q.front();
	test2.display();
}
