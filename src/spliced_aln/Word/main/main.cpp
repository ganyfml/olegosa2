// vim: set noexpandtab tabstop=2:

#include "../Word.hpp"
#include <seqan_api/SeqString.hpp>

using namespace std;

int main()
{
	int word_id = 1;
	int query_pos = 3;
	int rev_query_pos = 4;
	SeqString word_seq("ACG");
	Word temp(word_id, query_pos, rev_query_pos, word_seq);	

	temp.display();
}
