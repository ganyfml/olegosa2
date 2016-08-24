// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include "../../SeqStringSet.hpp"

using namespace std;

int main(int, char* argv[])
{
	SeqStringSet seqs;
	CharStringSet ids;
	CharStringSet quals;
	load_seqs_with_qual(argv[1], seqs, ids, quals);

	for(int i = 0; i < seqs.get_length(); ++i)
	{
		cout << "id: " << ids[i] << endl;
		cout << "seq: " << seqs[i] << endl;
		cout << "qual: " << quals[i] << endl << endl;
	}
}
