// vim: set noexpandtab tabstop=2:

#include "../../WordHitsGroupUtil.hpp"
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
	SeqString ref(argv[1]);
	SeqSuffixArray ref_SAIndex(ref);
	long ref_pos = atoi(argv[2]);
	cout << "forward: " << is_acceptor_splice_site_forward(ref_SAIndex, ref_pos) << endl;
	cout << "reverse: " << is_acceptor_splice_site_reverse(ref_SAIndex, ref_pos) << endl;
}
