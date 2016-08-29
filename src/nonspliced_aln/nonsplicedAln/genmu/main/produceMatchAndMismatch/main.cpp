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
	std::list<StateEntry> mutation_list;
	char next_char = argv[3][0];

	produceMatchAndMismatch(test, mutation_list, opt, next_char);

	int list_size = mutation_list.size();
	cout << "\n\n\nNum of new Entry: " << list_size << endl;
	for(int i = 0; i < list_size; ++i)
	{
		mutation_list.front().display();	
		mutation_list.pop_front();
		printf("\n\n");
	}
}
