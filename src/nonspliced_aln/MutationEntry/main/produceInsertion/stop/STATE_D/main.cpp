// vim: set noexpandtab tabstop=2:

#include "../../../../MutationEntry.hpp"
#include <queue>

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
	aln_nonspliceOpt opt;
	test.produceInsertion(mutation_queue, opt);
	cout << mutation_queue.size() << endl;
}
