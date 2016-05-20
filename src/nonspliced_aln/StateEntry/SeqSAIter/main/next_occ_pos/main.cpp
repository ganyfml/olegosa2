// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <queue>
#include "../../SeqSAIter.hpp"

using namespace seqan;
using namespace std;

int main(int argc, char* argv[])
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

	int occ_query = seq_sa_iter.num_occ();
	cout << "Number of query appeared: " << occ_query << endl;
	for(int i = 0; i < occ_query; ++i)
	{
		cout << i << " position: " << seq_sa_iter.next_occ_pos() << endl;
	}
}
