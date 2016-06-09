// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include "../../../SeqString.hpp"

using namespace std;

int main(int, char* argv[])
{
	SeqString query_seq(string("ATGC"));
	query_seq += "ATCG";
	std::cout << query_seq << std::endl;
}