// vim: set noexpandtab tabstop=2:
#include "../../Ref.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	SeqString ref_query((string(argv[1])));
	SeqSuffixArray ref_index(ref_query);

	Ref ref(ref_index);

	cout << ref.contains(SeqString(string(argv[2]))) << endl;
}
