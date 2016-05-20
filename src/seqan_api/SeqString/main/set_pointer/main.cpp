// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include <seqan/seq_io.h>
#include <seqan_api/SeqanAPIUtil.hpp>
#include "../../SeqString.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	typedef seqan::Dna5String SeqanString;

	SeqString test;
	cout << test << endl;
	test.set_pointer(new SeqanString("ATCG"));
	cout << test << endl;
}
