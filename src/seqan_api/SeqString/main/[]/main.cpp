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
	cout << origin_seq[0] << endl;
	if(origin_seq[0] == 'A')
	{
		printf("The first char is 'A'\n");
	}
}
