// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include "../../CharString.hpp"
#include <seqan/seq_io.h>

using namespace std;

int main()
{
	CharString origin_seq;
	origin_seq.set_pointer(new seqan::CharString("chr1"));
	CharString new_seq = origin_seq;
	cout << origin_seq << endl;
	cout << new_seq << endl;
}
