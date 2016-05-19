// vim: set noexpandtab tabstop=2:

#include <util/GapAndMM.hpp>

int main()
{
	GapAndMM test1;
	test1.num_mismatch = 1;
	test1.num_gapOpenRef = 2;
	test1.num_gapExtRef = 3;
	test1.num_gapOpenQuery = 4;
	test1.num_gapExtQuery = 5;

	GapAndMM test2;
	test2.num_mismatch = 2;
	test2.num_gapOpenRef = 3;
	test2.num_gapExtRef = 4;
	test2.num_gapOpenQuery = 5;
	test2.num_gapExtQuery = 6;

	GapAndMM test3 = test1 + test2;
	test3.display();
}
