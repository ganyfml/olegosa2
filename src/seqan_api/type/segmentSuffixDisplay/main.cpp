// vim: set noexpandtab tabstop=2:

#include <seqan/sequence.h>

using namespace std;

int main(int, char* argv[])
{
	seqan::Dna5String seq = "ATGC";
	auto segment = seqan::suffix(seq, 1);
}
