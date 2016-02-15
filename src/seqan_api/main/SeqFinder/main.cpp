// vim: set noexpandtab tabstop=2:
#include <SeqFinder.hpp>

using namespace std;

int main(int argc, char ** argv)
{
	string ref_file = argv[1];
	string index_file = argv[2];
	SeqString query = "ACG";

	SeqFinder finder {ref, query};
	while(finder.has_next())
	{
		cout << finder.next() << endl;
	}
}
