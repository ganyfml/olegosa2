// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <SeqString.hpp>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	string query ("ATGC");
	SeqString query_seq {query};
	query_seq.get_suffix(1);
	cout << query_seq << endl;
}
