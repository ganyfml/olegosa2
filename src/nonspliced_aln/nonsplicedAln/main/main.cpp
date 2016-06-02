// vim: set noexpandtab tabstop=2:

#include <string>
#include <iostream>
#include <queue>
#include <cstdlib>
#include "../nonsplicedAln.hpp"
#include <util/AlnResult.hpp>

using namespace std;

int main(int, char* argv[])
{
	SeqString query_seq((string(argv[2])));
	SeqString ref_seq((string(argv[1])));
	SeqSuffixArray ref_index(ref_seq);

	alnNonspliceOpt aln_opt;
	aln_opt.max_gapExt = atoi(argv[3]);
	aln_opt.max_gapOpen = atoi(argv[4]);
	aln_opt.max_mismatch = atoi(argv[5]);
	queue<AlnResult> result;
	nonsplicedAln(query_seq, result, ref_index, aln_opt);

	while(!result.empty())
	{
		result.front().display(ref_index);
		result.pop();
	}
}
