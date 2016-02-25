// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int argc, char** argv)
{
	SeqString query_seq(string("ATCG"));
	cout << query_seq.get_length() << endl;
}
