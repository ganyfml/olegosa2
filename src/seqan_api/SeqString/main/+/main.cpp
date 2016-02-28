// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include "../../SeqString.hpp"

using namespace std;

int main(int argc, char** argv)
{
	SeqString query_seq(string("ATGC"));
	
	char to_add = 'A';
	query_seq += to_add;
	std::cout << query_seq << std::endl;
}
