// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include "../../SeqString.hpp"

using namespace std;

int main(int, char* argv[])
{
	SeqString seq;
	CharString id;
	CharString qual;
	load_seq_with_qual(argv[1], seq, id, qual);

	cout << "id: " << id << endl;
	cout << "seq: " << seq << endl;
	cout << "qual: " << qual << endl;
}
