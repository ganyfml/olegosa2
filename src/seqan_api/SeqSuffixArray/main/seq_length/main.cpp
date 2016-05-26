// vim: set noexpandtab tabstop=2:

#include "../../SeqSuffixArray_conv.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	SeqString ref_seq(string("ACG"));
	SeqSuffixArray ref_SA(ref_seq);
	cout << ref_SA.seq_length() << endl;
}
