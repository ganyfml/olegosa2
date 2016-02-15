// vim: set noexpandtab tabstop=2:

#include <seqan_api.hpp>

using namespace std;

int main(int argc, char** argv)
{
	SeqString query_seq = "ATGC";
	int index_to_remove = 1;
	cout << change_stringRemove(query_seq, index_to_remove) << endl;
}
