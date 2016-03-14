// vim: set noexpandtab tabstop=2:
#include "../Ref.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	SeqString ref_query((string(argv[1])));
	SeqSuffixArray index(ref_query);
	Ref ref(index);

	SeqString query_seq((string(argv[2])));
	printf("Does reference seq contains query? %d\n", ref.contains(query_seq));

	ref.reset_finder();
	while(ref.find(query_seq))
	{
		printf("Find in position: %ld\n", ref.position());
	}

	printf("Third base of reference seq: %c\n", ref[2]);
}
