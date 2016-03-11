// vim: set noexpandtab tabstop=2:
#include "../../SeqFinder.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	SeqString index(string("ATGCAT"));
	SeqIndex seq_index(index);
	SeqFinder finder(seq_index);
	SeqString query_seq((string("A")));

	finder.clear();
	finder.find(query_seq);
	cout << finder.position() << endl;
}
