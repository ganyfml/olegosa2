// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int argc, char** argv)
{
	string query("ATGCACTAGCTAGC");
	SeqString query_seq {query};
	int pos_begin = 2;
	int pos_end = 5;
	cout << query_seq.get_infix(pos_begin, pos_end) << endl;
}
