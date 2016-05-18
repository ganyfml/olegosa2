// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <queue>
#include "../../../MutationEntry.hpp"

using namespace seqan;
using namespace std;

int main(int argc, char* argv[])
{
	typedef Index<Dna5String, seqan::IndexEsa<>> Dna5Index;
	Dna5Index ref((Dna5String(argv[1])));
	Dna5Index index(ref);
	Iterator<Dna5Index, TopDown<ParentLinks<>>>::Type it(index);

	MutationEntry test(it);
	test.state = MutationEntry::STATE_D;
	SeqString query(argv[2]);
	char match_char = query[test.query_pos];
	alnNonspliceOpt opt;
	MutationEntry new_entry;
	test.produceMatchEntry(new_entry, match_char);
	new_entry.display();
}
