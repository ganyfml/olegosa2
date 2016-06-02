// vim: set noexpandtab tabstop=2:

#include "../../Word.hpp"
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int, char* argv[])
{
	int word_id = 1;
	int word_length = 2;
	int query_pos = 3;
	int rev_query_pos = 4;
	SeqString word_seq = string("ACG");
	SeqString word_rseq = word_seq.get_reverse();
	Word temp(word_id, word_length, query_pos, rev_query_pos, word_seq, word_rseq);	

	temp.display();
}
