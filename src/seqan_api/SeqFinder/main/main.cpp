// vim: set noexpandtab tabstop=2:
#include "seqan_api/Ref.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	SeqString seq((string(argv[1])));
	SeqIndex seq_index(seq);
	createIndex(seq_index);
	SeqFinder finder(seq_index);
	SeqString query((string(argv[2])));

	cout << finder.find(query) << endl;
	cout << finder.location() << endl;
}