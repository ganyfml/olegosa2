// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <queue>
#include "../../../MutationEntry.hpp"

using namespace seqan;
using namespace std;

int main(int argc, char* argv[])
{
	typedef Index<Dna5String, seqan::IndexWotd<>> Dna5Index;
	Dna5Index index((Dna5String(argv[1])));
	Iterator<Dna5Index, TopDown<ParentLinks<>>>::Type it(index);

	MutationEntry test(it);
	test.state = MutationEntry::STATE_D;
	std::queue<MutationEntry> mutation_queue;
	alnNonspliceOpt opt;
	test.produceDeletion(mutation_queue, opt);

	int queue_size = mutation_queue.size();
	cout << queue_size << endl;
	for(int i = 0; i < queue_size; ++i)
	{
		mutation_queue.front().display();	
		mutation_queue.pop();
		printf("\n\n");
	}
}
