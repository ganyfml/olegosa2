// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <list>
#include "../../genmu.hpp"

using namespace seqan;
using namespace std;

int main(int, char* argv[])
{
	typedef Index<Dna5String, seqan::IndexEsa<>> Dna5Index;
	Dna5Index index((Dna5String(argv[1])));
	SeqSAIter it(index);

	StateEntry test(it);
	test.state = StateEntry::STATE_D;

	for(int i = 0; argv[2][i] != '\0'; ++i)
	{
		test.appendChar(argv[2][i]);
	}

	printf("Original entry: \n");
	test.display();
	printf("\n");

	alnNonspliceOpt opt;
	opt.max_mismatch = 1;
	priority_StateEntry_array mutation_array(opt);
	char next_char = argv[3][0];

	produceMatchAndMismatch(test, mutation_array, opt, next_char);

	mutation_array.display();

}
