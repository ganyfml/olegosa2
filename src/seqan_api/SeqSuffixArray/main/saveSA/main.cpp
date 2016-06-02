// vim: set noexpandtab tabstop=2:
#include "../../SeqSuffixArray.hpp"

using namespace std;

int main(int, char* argv[])
{
	SeqString ref_seq(string("ACG"));
	SeqSuffixArray ref_SA(ref_seq);
	ref_SA.saveSA(argv[1]);
}
