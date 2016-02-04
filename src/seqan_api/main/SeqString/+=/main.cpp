// vim: set noexpandtab tabstop=2:

#include <seqan_api.hpp>

using namespace std;

int main(int argc, char** argv)
{
	SeqString query_seq = "ATGC";
	SeqString seq2 = "GGGGGG";
	query_seq += "ATTTTTTT";
	query_seq += seq2;
	cout << query_seq << endl;
}
