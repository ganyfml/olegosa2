// vim: set noexpandtab tabstop=2:
#include <seqan_api/SeqFinder.hpp>
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
	string query_str = argv[2];
	string ref_str = argv[1]; 
	SeqString query(query_str);
	SeqString ref(ref_str);

	SeqIndex ref_index(ref);
	SeqFinder finder(ref_index);

	cout << finder.find(query) << endl;
}
