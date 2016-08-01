// vim: set noexpandtab tabstop=2:

#include "../../WordHitsGroupUtil.hpp"
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
	SeqString ref(argv[1]);
	SeqSuffixArray ref_SAIndex(ref);
	long ref_pos = atoi(argv[2]);
	bool revcomp = atoi(argv[3]);
	cout << is_acceptor_splice_site(ref_SAIndex, ref_pos, revcomp) << endl;
}
