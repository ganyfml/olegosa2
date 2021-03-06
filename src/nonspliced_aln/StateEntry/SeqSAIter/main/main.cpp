// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <queue>
#include "../SeqSAIter.hpp"

using namespace seqan;
using namespace std;

int main(int, char* argv[])
{
	typedef seqan::Dna5String SeqanString;
	typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;

	SeqanString seq((string(argv[1])));
	SeqanSA seq_index(seq);

	SeqSAIter seq_sa_iter(seq_index);
	cout << "Init iter seq: " << seq_sa_iter.get_prefix() << endl;
	for(int i = 0; argv[2][i] != '\0'; ++i)
	{
		char x = argv[2][i];
		cout << "Trying to go down: " << x << endl;
		cout << "Go Down successfully? " << seq_sa_iter.godown_char(x) << endl;
		cout << "Iter seq now: " << seq_sa_iter.get_prefix() << endl << endl;
	}
}
