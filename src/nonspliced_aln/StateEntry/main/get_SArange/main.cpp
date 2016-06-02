// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <queue>
#include "../../StateEntry.hpp"

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
	StateEntry entry(seq_sa_iter);

	for(int i = 0; argv[2][i] != '\0'; ++i)
	{
		char x = argv[2][i];
		entry.appendChar(x);
	}

	seqan::Pair<unsigned> sa_range = entry.get_SArange();
	cout << "Number of query appeared: " << sa_range.i2 - sa_range.i1 << endl;

	cout << "Hit in pos: " << endl;
	for(unsigned int i = sa_range.i1; i < sa_range.i2; ++i)
	{
		cout << saAt(i, seq_index) << " ";
	}

	cout << endl;
}
