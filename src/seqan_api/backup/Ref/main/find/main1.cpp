// vim: set noexpandtab tabstop=2:
#include "../../Ref.hpp"
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
	SeqString ref_query((string("ATGCAT")));
	SeqIndex ref_index(ref_query);

	Ref ref(ref_index);
	SeqString query_seq(string("A"));

	ref.reset_finder();
	while(ref.find(query_seq))
	{
		cout << ref.position() << endl;
	}
}
