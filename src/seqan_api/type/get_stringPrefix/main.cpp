// vim: set noexpandtab tabstop=2:

#include <seqan/seq_io.h>

using namespace std;

int main(int, char* argv[])
{
	seqan::Dna5String query_seq = "ATGC";
	int prefix_index = 1;
	int a = prefix(query_seq, prefix_index);
}
