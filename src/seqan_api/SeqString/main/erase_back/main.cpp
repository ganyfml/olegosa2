// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include "seqan_api/SeqString.hpp"

using namespace std;

int main(int argc, char** argv)
{
	string query ("ATGC");
	SeqString query_seq (query);
	cout << query_seq << endl;
	query_seq.erase_back();
	cout << query_seq << endl;
}