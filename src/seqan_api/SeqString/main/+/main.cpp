// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int argc, char** argv)
{
	string query("ATGC");
	SeqString query_seq {query};
	
	char to_add = 'A';
	query_seq += to_add;
	std::cout << query_seq << std::endl;
}
