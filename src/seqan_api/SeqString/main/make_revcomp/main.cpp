// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include "../../SeqString.hpp"

using namespace std;

int main()
{
	SeqString query_seq(string("ATGC"));
	cout << query_seq << endl;
	query_seq.make_revcomp();
	cout << query_seq << endl;
}
