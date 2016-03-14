// vim: set noexpandtab tabstop=2:
#include "../../Ref.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	SeqString ref_seq((string(argv[1])));
	SeqSuffixArray ref_index(ref_seq);

	Ref ref(ref_index);
	ref.find(SeqString((string(argv[2]))));
	cout << ref.position() << endl;
}
