// vim: set noexpandtab tabstop=2:
#include <seqan_api/SeqFinder.hpp>
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
	SeqString ref((string(argv[1])));
	SeqIndex ref_index(ref);
	SeqFinder finder(ref_index);

	SeqString query((string(argv[2])));
	cout << finder.find(query) << endl;
}
