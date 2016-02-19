// vim: set noexpandtab tabstop=2:

#include <seqan/seq_io.h>

using namespace std;

int main(int argc, char** argv)
{
	seqan::Dna5String query_seq = "ATGCATCGATCGATCGACTAGCTACGACTCAGTACGCT";
	int infix_start = 0;
	int infix_end = 1;
	int a = infix(query_seq, infix_start, infix_end);
}
