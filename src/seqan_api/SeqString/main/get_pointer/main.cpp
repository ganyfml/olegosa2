// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include <seqan/seq_io.h>
#include <seqan_api/SeqanAPIUtil.hpp>
#include "../../SeqString.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	SeqString query_seq(string("ATCG"));
	constVoid2localType<seqan::Dna5String>(query_seq.get_pointer());
}
