// vim: set noexpandtab tabstop=2:

#include <list>
#include "../../splicedAln.hpp"
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int argc, char* argv[])
{
	SeqString ref_seq((string(argv[1])));
	SeqSuffixArray ref_SA(ref_seq);

	SeqString query((string(argv[2])));

	AlnSpliceOpt opt;
	opt.word_length = 2;
	opt.word_max_overlap = 1;

	list<WordPtr> words;
	generate_words(query, words, opt);

	for(auto iter = words.begin(); iter != words.end(); ++iter)
	{
		(*iter)->display();
	}

	std::list<WordHitPtr> wordHitList;
	collect_wordHits(words, wordHitList, ref_SA, opt);

	for(auto iter = wordHitList.begin(); iter != wordHitList.end(); ++iter)
	{
		(*iter)->display();
	}
}
