// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <queue>
#include "../../SeqSAIter.hpp"

using namespace seqan;
using namespace std;

int main(int, char* argv[])
{
	typedef seqan::Dna5String SeqanString;
	typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
	typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

	SeqanString seq((string(argv[1])));
	SeqanSA seq_index(seq);

	SeqSAIter seq_sa_iter(seq_index);
	for(int i = 0; argv[2][i] != '\0'; ++i)
	{
		char x = argv[2][i];
		seq_sa_iter.godown_char(x);
	}
 	seq_sa_iter.display();

	cout << "Number of query appeared: " << seq_sa_iter.num_occ() << endl;
}
