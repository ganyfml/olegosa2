// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <SeqString.hpp>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	string query("ATGC");
	SeqString query_seq {query};
	int prefix_pos = 2;
	cout << query_seq.get_prefix(prefix_pos) << endl;
}
