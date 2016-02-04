// vim: set noexpandtab tabstop=2:

#include <seqan_api.hpp>

using namespace std;

int main(int argc, char** argv)
{
	SeqString query_seq = "ATGC";
	int index_to_add = 1;
	int value_to_add = 'T';
	cout << change_stringInsert(query_seq, index_to_add, value_to_add) << endl;
}
