// vim: set noexpandtab tabstop=2:

#include <seqan/seq_io.h>

using namespace std;

int main(int, char* argv[])
{
	seqan::Dna5String query_seq = "ATGCATACATCAGTCAGCT";
	int suffix_index = 1;
	int c = suffix(query_seq, suffix_index);
}
