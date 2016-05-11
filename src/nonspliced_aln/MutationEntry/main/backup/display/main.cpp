// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <queue>
#include "../../MutationEntry.hpp"

using namespace seqan;
using namespace std;

int main(int argc, char* argv[])
{
	typedef Index<Dna5String, seqan::IndexEsa<>> Dna5Index;
	Dna5Index index((Dna5String(argv[1])));
	Iterator<Dna5Index, TopDown<ParentLinks<>>>::Type it(index);

	MutationEntry test(it);

	test.display();
	goDown(test.ref_iter, 'A');
	test.display();
}
