// vim: set noexpandtab tabstop=2:
#include "../../Ref/Ref.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	SeqString seq((string(argv[1])));
	SeqSuffixArray seq_index(seq);
	SeqFinder finder(seq_index);
	SeqString query((string(argv[2])));

	cout << finder.find(query) << endl;
	cout << finder.position() << endl;
}
