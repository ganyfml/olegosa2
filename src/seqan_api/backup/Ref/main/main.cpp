// vim: set noexpandtab tabstop=2:
#include "../Ref.hpp"
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
	SeqString ref_query((string("ATGC")));
	SeqIndex index(ref_query);
	Ref ref(index);

	ref.reset_finder();
	SeqString query_seq((string("T")));
	while(ref.find(query_seq))
	{
		printf("Find in position: %ld\n", ref.position());
	}
}
