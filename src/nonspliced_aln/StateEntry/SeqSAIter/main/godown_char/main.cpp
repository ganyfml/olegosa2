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
	for(int i = 0; argv[2][i] != '\0'; ++i)
	{
		char godown_char = argv[2][i];
		cout << "Trying to go down: " << godown_char << endl;
		cout << "Go Down successfully? " << seq_sa_iter.godown_char(godown_char) << endl;
		seq_sa_iter.display();
		printf("\n");
	}
}
