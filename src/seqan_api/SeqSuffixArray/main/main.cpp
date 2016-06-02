// vim: set noexpandtab tabstop=2:
#include "../SeqSuffixArray.hpp"

using namespace std;

int main(int, char* argv[])
{
	SeqString ref_seq(string("ACG"));
	SeqSuffixArray ref_index(ref_seq);
	ref_index.saveSA((string(argv[1])));

	string file_name = string(argv[1]);
	SeqSuffixArray ref_load(file_name);
}
