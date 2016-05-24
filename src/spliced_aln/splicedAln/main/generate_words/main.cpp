// vim: set noexpandtab tabstop=2:

#include <list>
#include "../../splicedAln.hpp"
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int argc, char* argv[])
{
	AlnSpliceOpt opt;
	opt.word_length = 5;
	opt.word_max_overlap = 2;

	SeqString query((string(argv[1])));
	list<WordPtr> words;
	generate_words(query, words, opt);

	for(auto iter = words.begin(); iter != words.end(); ++iter)
	{
		(*iter)->display();
	}
}
