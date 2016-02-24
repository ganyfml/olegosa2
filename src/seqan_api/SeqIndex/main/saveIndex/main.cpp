// vim: set noexpandtab tabstop=2:
#include <seqan_api/SeqIndex.hpp>

using namespace std;

int main(int argc, char ** argv)
{
	string ref_seq = "ACG";
	SeqString ref(ref_seq);

	SeqIndex ref_index(ref);
	createIndex(ref_index);

	saveIndex(ref_index, argv[1]);
}
