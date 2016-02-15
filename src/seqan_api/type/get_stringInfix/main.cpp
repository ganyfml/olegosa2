// vim: set noexpandtab tabstop=2:

#include <seqan_api.hpp>

using namespace std;

int main(int argc, char** argv)
{
	SeqString query_seq = "ATGCATCGATCGATCGACTAGCTACGACTCAGTACGCT";
	int infix_start = atoi(argv[1]);
	int infix_end = atoi(argv[2]);
	int a = get_stringInfix(query_seq, infix_start, infix_end);
}
