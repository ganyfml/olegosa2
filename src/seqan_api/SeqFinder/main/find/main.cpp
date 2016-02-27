// vim: set noexpandtab tabstop=2:
#include "seqan_api/Ref.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	SeqIndex seq_index((string(argv[1])));
	createIndex(seq_index);
	SeqFinder finder(seq_index);
	std::string query_seq = argv[2];

	cout << finder.find(query_seq) << endl;
}
