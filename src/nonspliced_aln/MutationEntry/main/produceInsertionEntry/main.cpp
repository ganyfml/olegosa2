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
	Dna5Index index(ref);
	SeqSAIter it(index);

	MutationEntry test(it);
	MutationEntry new_entry;
	alnNonspliceOpt opt;
	opt.max_gapOpen = 1;
	char insert_char = argv[2][0];
	bool produce_succ = test.produceInsertionEntry(new_entry, opt, insert_char);
	printf("Produces successfully? %d\n", produce_succ);
	if(produce_succ) new_entry.display();
}
