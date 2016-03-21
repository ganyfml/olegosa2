// vim: set noexpandtab tabstop=2:
#include "../SeqFinder.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	SeqString seq((string(argv[1])));
	SeqSuffixArray seq_SA(seq);
	SeqFinder finder(seq_SA);
	SeqString query((string(argv[2])));

	finder.clear();
	while(finder.find(query))
	{
		cout << finder.position() << endl;
	}
}
