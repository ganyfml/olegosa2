// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <seqan_api/SeqString.hpp>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	string query("ATGC");
	SeqString query_seq {query};
	int begin_pos = 1;
	int end_pos = 2;
	cout << query_seq.get_infix(begin_pos, end_pos) << endl;
}
