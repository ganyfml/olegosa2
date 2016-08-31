// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <list>
#include "../../priority_StateEntry_array.hpp"

using namespace seqan;
using namespace std;

int main(int, char* argv[])
{
	typedef Index<Dna5String, seqan::IndexEsa<>> Dna5Index;
	Dna5Index index((string("ATCG")));
	SeqSAIter it(index);
	StateEntry test(it);
	test.gap_mm.num_gapOpenRef = 1;
	test.gap_mm.num_mismatch = 1;

	alnNonspliceOpt opt;
	opt.max_gapOpen = 1;
	opt.max_gapExt = 2;
	opt.max_mismatch = 3;

	priority_StateEntry_array test_array(opt);
	test_array.push(test, opt);

	StateEntry best_entry;
	int worst_score = atoi(argv[1]);
	if(test_array.pop_best(best_entry, worst_score))
	{
		printf("Get score better or same then %d\n", worst_score);
		printf("Entry score: %d\n", best_entry.get_score(opt));
	}
	else
	{
		printf("No entry score better or same then %d\n", worst_score);
	}
}
