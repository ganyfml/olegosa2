// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <queue>
#include "../../genmu.hpp"

using namespace seqan;
using namespace std;

int main(int argc, char* argv[])
{
	typedef Index<Dna5String, seqan::IndexEsa<>> Dna5Index;
	Dna5Index index((Dna5String(argv[1])));
	SeqSAIter it(index);

	StateEntry test(it);
	test.state = StateEntry::STATE_M;

	for(int i = 0; argv[2][i] != '\0'; ++i)
	{
		test.appendChar(argv[2][i]);
	}

	printf("Original entry: \n");
	test.display();
	printf("\n");

	alnNonspliceOpt opt;
	opt.max_gapOpen = atoi(argv[3]);
	opt.max_gapExt = atoi(argv[4]);
	std::queue<StateEntry> mutation_queue;

	produceInsertionFromM(test, mutation_queue, opt);

	int queue_size = mutation_queue.size();
	cout << "\n\n\nNum of new Entry: " << queue_size << endl;
	for(int i = 0; i < queue_size; ++i)
	{
		mutation_queue.front().display();	
		mutation_queue.pop();
		printf("\n\n");
	}
}
