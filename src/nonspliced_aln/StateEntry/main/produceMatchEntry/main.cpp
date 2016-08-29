// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <list>
#include "../../StateEntry.hpp"

using namespace seqan;
using namespace std;

int main(int, char* argv[])
{
	typedef Index<Dna5String, seqan::IndexEsa<>> Dna5Index;
	Dna5Index ref((Dna5String(argv[1])));
	SeqSAIter it(ref);

	StateEntry test(it);
	SeqString query(argv[2]);
	StateEntry new_entry;
	test.produceMatchEntry(new_entry);
	new_entry.display();
}
