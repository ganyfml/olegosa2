// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../../StateEntry.hpp"

using namespace std;
using namespace seqan;

int main(int, char* argv[])
{
	typedef Index<Dna5String, seqan::IndexEsa<>> Dna5Index;
	Dna5Index index((Dna5String(argv[1])));
	SeqSAIter it(index);

	StateEntry test(it);
	test.gap_mm.num_gapOpenRef = 1;
	test.gap_mm.num_gapOpenQuery = 2;
	test.gap_mm.num_gapExtRef = 3;
	test.gap_mm.num_gapExtQuery = 4;
	test.gap_mm.num_mismatch = 5;

	alnNonspliceOpt opt;
	cout << test.get_score(opt) << endl;
}
