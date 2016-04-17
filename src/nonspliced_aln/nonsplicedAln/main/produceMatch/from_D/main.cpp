// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <queue>
#include "../../../nonsplicedAln.hpp"

using namespace seqan;
using namespace std;

int main(int argc, char* argv[])
{
	typedef Index<Dna5String, seqan::IndexEsa<>> Dna5Index;
	Dna5Index index((Dna5String(argv[1])));
	Iterator<Dna5Index, TopDown<ParentLinks<>>>::Type it(index);

	MutationEntry test(it);
	test.state = MutationEntry::STATE_D;
	std::queue<MutationEntry> mutation_queue;
	alnNonspliceOpt opt;
	char next_char = rawtextAt(test.ref_pos, index);
	produceMismatch(test, mutation_queue, opt, next_char);

	int queue_size = mutation_queue.size();
	cout << queue_size << endl;
	for(int i = 0; i < queue_size; ++i)
	{
		mutation_queue.front().display();	
		mutation_queue.pop();
		printf("\n\n");
	}
}
