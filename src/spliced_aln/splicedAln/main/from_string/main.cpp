// vim: set noexpandtab tabstop=2:

#include "../../splicedAln.hpp"

using namespace std;

int main(int, char* argv[])
{
	//Construct ref_SA
	SeqString ref_seq((string(argv[1])));
	SeqSuffixArray ref_SA(ref_seq);

	SeqString query((string(argv[2])));

	AlnSpliceOpt opt;
	opt.word_length = 5;
	opt.word_max_overlap = 0;
	opt.min_anchor_size = 3;

	splicedAln(query, ref_SA, opt);
}
