// vim: set noexpandtab tabstop=2:
#include "../../Ref.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	SeqString ref_seq((string("ATCTTCA")));
	SeqIndex ref_index(ref_seq);

	Ref ref(ref_index);
	ref.reset_finder();
	while(ref.find(SeqString((string("T")))))
	{
		cout << ref.position() << endl;
	}
}
