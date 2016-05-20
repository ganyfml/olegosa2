// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../../AlnResult.hpp"
#include <seqan/seq_io.h>

using namespace seqan;
using namespace std;

int main(int argc, char* argv[])
{
	typedef seqan::Dna5String SeqanString;

	SeqString seq_test;
	seq_test.set_pointer(new SeqanString("ATCG"));

	AlnResult test;
	test.seq = seq_test;
	test.num_hits = 1;
	test.ref_pos = 2;

	test.display();
}
