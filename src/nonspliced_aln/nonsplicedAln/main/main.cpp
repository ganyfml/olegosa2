// vim: set noexpandtab tabstop=2:

#include <string>
#include <iostream>
#include <queue>
#include <cstdlib>
#include "../nonsplicedAln.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	SeqString query_seq((string(argv[2])));
	SeqString ref_seq((string(argv[1])));
	SeqSuffixArray ref_index(ref_seq);

	alnNonspliceOpt aln_opt;
	aln_opt.max_gapExt = atoi(argv[3]);
	aln_opt.max_gapOpen = atoi(argv[4]);
	aln_opt.max_mismatch = atoi(argv[5]);
	nonsplicedAln(query_seq, ref_index, aln_opt);
}
