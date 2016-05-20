// vim: set noexpandtab tabstop=2:

#include <string>
#include <iostream>
#include <queue>
#include "../../nonsplicedAln.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	SeqString query_seq((string(argv[2])));
	SeqString ref_seq((string(argv[1])));
	SeqSuffixArray ref_index(ref_seq);

	alnNonspliceOpt aln_opt;
	nonsplicedAln(query_seq, ref_index, aln_opt);
}
