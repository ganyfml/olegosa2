// vim: set noexpandtab tabstop=2:
#include <seqan_api.hpp>

using namespace std;

int main(int argc, char ** argv)
{
	string ref_file = argv[1];
	string index_file = argv[2];
	Seq ref(ref_file, index_file);
	ref.create_SA(0);
	ref.load_SA();
	SeqString query = "ACG";

	SeqFinder finder {ref, query};
	while(finder.has_next())
	{
		cout << finder.next() << endl;
	}
}
