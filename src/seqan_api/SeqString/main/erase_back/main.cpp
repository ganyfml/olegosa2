// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <SeqString.hpp>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	string query ("ATGC");
	SeqString query_seq (query);
	cout << query_seq << endl;
	query_seq.erase_back();
	cout << query_seq << endl;
}
