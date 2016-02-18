// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include "seqan_api/SeqString.hpp"

using namespace std;

int main(int argc, char** argv)
{
	string query {"ATGC"};
	SeqString query_seq {query};
	int suffix_pos = 1;
	cout << query_seq.get_suffix(suffix_pos) << endl;
}
