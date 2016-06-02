// vim: set noexpandtab tabstop=2:
#include "../../SeqFinder.hpp"
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
	SeqString ref(string("ATGCAT"));
	SeqSuffixArray seq_SA(ref);
	SeqFinder finder(seq_SA);
	SeqString query_seq((string("A")));

	finder.clear();
	while(finder.find(query_seq))
	{
		cout << finder.position() << endl;	
	}
}
