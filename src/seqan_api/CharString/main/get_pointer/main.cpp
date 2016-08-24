// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include <seqan/seq_io.h>
#include <seqan_api/SeqanAPIUtil.hpp>
#include "../../CharString.hpp"

using namespace std;

int main()
{
	CharString query_seq(string("chr1"));
	constVoid2localType<seqan::Dna5String>(query_seq.get_pointer());
}
