// vim: set noexpandtab tabstop=2:
#include "../../SeqSuffixArray.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	SeqString ref_seq((string(argv[1])));
	SeqSuffixArray ref_SA(ref_seq);
	cout << ref_SA.SAIndex2SeqPos(4) << endl;
	cout << ref_SA.SAIndex2SeqPos(5) << endl;
}
