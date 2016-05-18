// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <queue>
#include "../../../SeqSAIter.hpp"

using namespace seqan;
using namespace std;

int main(int argc, char* argv[])
{
	typedef seqan::Dna5String SeqanString;
	typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
	typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

	SeqanString seq((string(argv[1])));
	SeqanSA seq_index(seq);

	SeqSAIter iter;
}
