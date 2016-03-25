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

	GapAndMM test2(test1);
	test2.display();
}
