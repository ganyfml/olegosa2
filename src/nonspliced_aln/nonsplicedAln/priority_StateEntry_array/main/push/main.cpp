// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <list>
#include "../../priority_StateEntry_array.hpp"

using namespace seqan;
using namespace std;

int main()
{
	typedef Index<Dna5String, seqan::IndexEsa<>> Dna5Index;
	Dna5Index index((string("ATCG")));
	SeqSAIter it(index);

	alnNonspliceOpt opt;
	opt.max_gapOpen = 1;
	opt.max_gapExt = 2;
	opt.max_mismatch = 3;
	priority_StateEntry_array test_array(opt);

	StateEntry test(it);
	test.gap_mm.num_gapOpenRef = 1;
	test.gap_mm.num_mismatch = 1;

	printf("Pusing the entry with score: %d\n", test.get_score(opt));
	test_array.push(test, opt);

	test_array.display();
}
