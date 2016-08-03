// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include "../../SeqString.hpp"

using namespace std;

int main()
{
	SeqString query_seq(string("ATGC"));
	cout << query_seq << endl;
	SeqString seq_infix = query_seq.get_infix(1, 2);
	cout << seq_infix << endl;
}
