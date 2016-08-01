// vim: set noexpandtab tabstop=2:

#include "../../WordHitsGroupUtil.hpp"
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
	SeqString ref(argv[1]);
	SeqSuffixArray ref_SAIndex(ref);
	long ref_pos = atoi(argv[2]);
	SpliceType::Value splice_type = static_cast<SpliceType::Value>(atoi(argv[3]));
	Strand::Value splice_strand = static_cast<Strand::Value>(atoi(argv[4]));
	cout << is_splice_site_by_refPos(ref, ref_pos, splice_type, splice_strand) << endl;
}
