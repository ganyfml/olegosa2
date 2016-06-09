// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include "../../SeqString.hpp"
#include <seqan/seq_io.h>

using namespace std;

int main(int, char* argv[])
{
	typedef seqan::Dna5String SeqanString;

	SeqString origin_seq;
	origin_seq.set_pointer(new SeqanString("ATCG"));
	SeqString new_seq = origin_seq;
	cout << origin_seq << endl;
	cout << new_seq << endl;
}
