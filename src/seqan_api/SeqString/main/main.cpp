// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include "../SeqString.hpp"
#include "../../SeqanAPIUtil/SeqanAPIUtil.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	SeqString query_seq(string("ATGC"));
	
	query_seq += "AGG";
	cout << "query_seq: " << query_seq << endl;
	cout << "The third base of query_seq is " << query_seq[2] << endl;
	query_seq.erase_back();
	cout << "After erase the last base, the query_seq is " << query_seq << endl;
}
