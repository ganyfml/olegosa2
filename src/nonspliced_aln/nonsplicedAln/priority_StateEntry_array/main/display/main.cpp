// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <nonspliced_aln/alnNonspliceOpt.hpp>
#include "../../priority_StateEntry_array.hpp"

using namespace std;

int main()
{
	alnNonspliceOpt opt;
	opt.max_gapOpen = 1;
	opt.max_gapExt = 2;
	opt.max_mismatch = 3;

	priority_StateEntry_array test_array(opt);
	test_array.display();
}
