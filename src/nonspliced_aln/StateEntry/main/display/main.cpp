// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <queue>
#include "../../StateEntry.hpp"

using namespace seqan;
using namespace std;

int main(int, char* argv[])
{
	typedef Index<Dna5String, seqan::IndexEsa<>> Dna5Index;
	Dna5Index index((Dna5String(argv[1])));
	SeqSAIter it(index);

	StateEntry test(it);

	test.display();
	test.appendChar('A');
	test.display();
}
