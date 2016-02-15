// vim: set noexpandtab tabstop=2:

#include <seqan_api.hpp>

using namespace std;

int main(int argc, char** argv)
{
	SeqString query_seq = "ATGC";
	int prefix_index = atoi(argv[1]);
	int a = get_stringPrefix(query_seq, prefix_index);
}
