// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <queue>
#include "../../MutationEntry.hpp"

using namespace seqan;
using namespace std;

int main(int argc, char* argv[])
{
	typedef Index<Dna5String, seqan::IndexEsa<>> Dna5Index;
	Dna5Index ref((Dna5String(argv[1])));
	SeqSAIter ref_it(ref);

	char exist_part = argv[2][0];
	if(exist_part != '\0')
	{
		ref_it.godown_char(exist_part);
	}

	MutationEntry test(ref_it);
	MutationEntry new_entry;
	alnNonspliceOpt opt;
	opt.max_mismatch = 1;
	char mismatch_char = argv[3][0];
	bool produce_succ = test.produceMismatchEntry(new_entry, opt, mismatch_char);
	printf("Produces successfully? %d\n", produce_succ);
	if(produce_succ)
	{
		new_entry.display();
	}
}
