// vim: set noexpandtab tabstop=2:

#include <seqan_api.hpp>

using namespace std;

int main(int argc, char** argv)
{
	seqan::Dna5String query_seq = "ATGCATACATCAGTCAGCT";
	int suffix_index = 1;
	int c = suffix(query_seq, suffix_index);
}