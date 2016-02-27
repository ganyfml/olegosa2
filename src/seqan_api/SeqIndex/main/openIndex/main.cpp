// vim: set noexpandtab tabstop=2:
#include "seqan_api/SeqIndex.hpp"

using namespace std;

int main(int argc, char ** argv)
{
	SeqString ref_seq(string("ACG"));
	SeqIndex ref_index(ref_seq);
	createIndex(ref_index);
	saveIndex(ref_index, argv[1]);

	SeqIndex ref_load;
	openIndex(ref_load, argv[1]);
}
