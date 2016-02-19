// vim: set noexpandtab tabstop=2:
#include <seqan_api/SeqFinder.hpp>

using namespace std;

int main(int argc, char ** argv)
{
	string query_str = "ACG";
	string ref_str = "ACGAGCTACGATCGATCGACTGACTGACAGCTCGACTGACTGACTGCTACGCTAGACTACGACTAGCTACGAACG"; 
	SeqString query(query_str);
	SeqString ref(ref_str);


	SeqIndex ref_index(ref);
	SeqFinder finder(ref_index, query);
	while(finder.has_next())
	{
		cout << finder.next() << endl;
	}
}
