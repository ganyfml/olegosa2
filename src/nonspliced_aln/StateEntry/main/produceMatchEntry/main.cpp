// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <queue>
#include "../../StateEntry.hpp"

using namespace seqan;
using namespace std;

int main(int argc, char* argv[])
{
	typedef Index<Dna5String, seqan::IndexEsa<>> Dna5Index;
	Dna5Index ref((Dna5String(argv[1])));
	SeqSAIter it(ref);

	StateEntry test(it);
	SeqString query(argv[2]);
	char match_char = query[test.query_pos];
	StateEntry new_entry;
	bool produce_succ = test.produceMatchEntry(new_entry, match_char);
	printf("Produces successfully? %d\n", produce_succ);
	if(produce_succ)
		new_entry.display();
}
