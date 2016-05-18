// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <queue>
#include "../../../genmu.hpp"

using namespace seqan;
using namespace std;

int main(int argc, char* argv[])
{
	typedef Index<Dna5String, seqan::IndexEsa<>> Dna5Index;
	Dna5Index index((Dna5String(argv[1])));
	SeqSAIter it(index);

	MutationEntry test(it);
	test.state = MutationEntry::STATE_I;
	printf("Original entry: \n");
	test.display();
	printf("\n");

	std::queue<MutationEntry> mutation_queue;
	alnNonspliceOpt opt;

	produceDeletion(test, mutation_queue, opt);

	int queue_size = mutation_queue.size();
	cout << "Num of new Entry: " << queue_size << endl;
	for(int i = 0; i < queue_size; ++i)
	{
		mutation_queue.front().display();	
		mutation_queue.pop();
		printf("\n\n");
	}
}
