// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include "../../SeqString.hpp"

using namespace std;

int main()
{
	SeqString query_seq(string("ATGC"));
	SeqString result = query_seq + SeqString("ATCG");
	std::cout << result << std::endl;
	std::cout << query_seq << std::endl;
}
