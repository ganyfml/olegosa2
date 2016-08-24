// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <string>
#include "../../SeqString.hpp"

using namespace std;

int main(int, char* argv[])
{
	SeqString seq;
	CharString id;
	load_seq(argv[1], seq, id);

	cout << "id: " << id << endl;
	cout << "seq: " << seq << endl;
}
