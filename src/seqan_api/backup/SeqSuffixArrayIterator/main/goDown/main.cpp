// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../../SeqSuffixArrayIterator.hpp"

using namespace std;

int main(int, char* argv[])
{
	SeqString seq((string(argv[1])));
	SeqSuffixArray ref_sa(seq);

	SeqSuffixArrayIterator ref_SA_iter(ref_sa);
	char godown_char = argv[2][0];
	cout << "Contain char? " << ref_SA_iter.godown_char(godown_char) << endl;
}
