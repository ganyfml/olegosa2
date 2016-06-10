// vim: set noexpandtab tabstop=2:

#include <list>
#include "../../splicedAlnUtil.hpp"
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int, char* argv[])
{
	AlnSpliceOpt opt;
	opt.word_length = atoi(argv[1]);
	opt.word_max_overlap = atoi(argv[2]);

	SeqString query((string(argv[3])));
	vector<WordPtr> words;
	generate_words(query, words, opt);

	printf("Word_seq\tWord_r_seq\tQuery_pos\n");

	for(auto iter = words.begin(); iter != words.end(); ++iter)
	{
		cout << (*iter)->seq << "\t" << (*iter)->r_seq << "\t" << (*iter)->query_pos << endl;
	}
}
