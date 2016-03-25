// vim: set noexpandtab tabstop=2:

#include <util/GapAndMM.hpp>
#include <iostream>

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
	cout << "number of gap extension: " << test1.num_gapExt() << endl;
}
