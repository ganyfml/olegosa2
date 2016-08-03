// vim: set noexpandtab tabstop=2:

#include "../../SeqSuffixArray_conv.hpp"

using namespace std;

int main(int, char* argv[])
{
	SeqString ref_seq(string("ATCG"));
	SeqSuffixArray ref_SA(ref_seq);

	cout << ref_SA.get_infixSeq(1, 2)<< endl;
}
