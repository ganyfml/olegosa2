// vim: set noexpandtab tabstop=2:

#include <string>
#include <iostream>
#include <list>
#include <cstdlib>
#include "../exactMatchAln.hpp"
#include <util/AlnResult.hpp>

using namespace std;

int main(int, char* argv[])
{
	SeqString query_seq((string(argv[2])));
	SeqString ref_seq((string(argv[1])));
	SeqSuffixArray ref_index(ref_seq);

	alnNonspliceOpt aln_opt;
	list<AlnResult> result;
	exactMatchAln(query_seq, result, ref_index, aln_opt);

	while(!result.empty())
	{
		result.front().display(ref_index);
		result.pop_front();
	}
}
