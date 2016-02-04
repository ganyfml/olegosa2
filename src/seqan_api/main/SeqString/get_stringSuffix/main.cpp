// vim: set noexpandtab tabstop=2:

#include <seqan_api.hpp>

using namespace std;

int main(int argc, char** argv)
{
	SeqString query_seq = "ATGCATACATCAGTCAGCT";
	int suffix_index = atoi(argv[1]);
	cout << get_stringSuffix(query_seq, suffix_index) << endl;
}
