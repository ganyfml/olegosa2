// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../../SeqSuffixArrayIterator.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	SeqString seq((string(argv[1])));
	SeqSuffixArray ref_sa(seq);

	SeqSuffixArrayIterator ref_SA_iter(ref_sa);
	SeqString query((string(argv[2])));
	cout << "Contain query? " << ref_SA_iter.goDown(query) << endl;
}
