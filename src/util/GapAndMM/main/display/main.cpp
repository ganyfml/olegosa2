// vim: set noexpandtab tabstop=2:

#include <util/GapAndMM.hpp>

int main()
{
	GapAndMM test;
	test.num_mismatch = 1;
	test.num_gapOpenRef = 2;
	test.num_gapExtRef = 3;
	test.num_gapOpenQuery = 4;
	test.num_gapExtQuery = 5;

	test.display();
}
