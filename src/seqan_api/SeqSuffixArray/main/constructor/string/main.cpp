// vim: set noexpandtab tabstop=2:

#include "../../../SeqSuffixArray.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	string index_file_name = string(argv[1]);
	SeqSuffixArray ref_load(index_file_name);

	for(int i = 0; i < ref_load.seq_length(); ++i)
	{
		cout << ref_load.char_at(i) << endl;
	}
}
