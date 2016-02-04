// vim: set noexpandtab tabstop=2:

#include <seqan_api.hpp>

using namespace std;

int main(int argc, char** argv)
{
	SeqString query_seq = "ATGC";
	if(query_seq[0] == 'A')
		cout << "Equal" << endl;
	else cout << "Not Equal" << endl;
}
