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

	SeqanString seq((string(argv[1])));
	SeqanSA seq_index(seq);

	SeqSAIter seq_sa_iter(seq_index);
	printf("Init iter seq: ");
	seq_sa_iter.display();
	SeqString godown_seq(argv[2]);
	for(int i = 0; i < godown_seq.get_length(); ++i)
	{
		char x = godown_seq[i];
		seq_sa_iter.godown_char(x);
	}

	cout << "Result seq length: " << seq_sa_iter.get_repLength() << endl;
}
