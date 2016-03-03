// vim: set noexpandtab tabstop=2:
#include "../../../Ref/Ref.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	SeqString index((SeqString(string(argv[1]))));
	SeqIndex seq_index(index);
	SeqFinder finder(seq_index);
	SeqString query_seq((string(argv[2])));

	cout << finder.find(query_seq) << endl;
}
