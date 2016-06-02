// vim: set noexpandtab tabstop=2:

#include "../../SeqSuffixArray_conv.hpp"

using namespace std;

int main(int, char* argv[])
{
	SeqString ref_seq(string("ACG"));
	SeqSuffixArray ref_SA(ref_seq);

	for(int i = 0; i < ref_SA.seq_length(); ++i)
	{
		cout << ref_SA.char_at(i);
	}
	cout << endl;
}
