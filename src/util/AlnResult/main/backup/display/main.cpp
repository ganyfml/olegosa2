// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../../AlnResult.hpp"
#include <seqan/seq_io.h>

using namespace seqan;
using namespace std;

int main(int, char* argv[])
{
	typedef seqan::Dna5String SeqanString;

	SeqString seq_test;
	seq_test.set_pointer(new SeqanString("ATCG"));

	AlnResult test;
	test.SA_index_high = 4;
	test.SA_index_low = 3;
	test.num_hits = 1;
	test.ref_pos = 2;
	test.seq_length = 5;

	test.display();
}
