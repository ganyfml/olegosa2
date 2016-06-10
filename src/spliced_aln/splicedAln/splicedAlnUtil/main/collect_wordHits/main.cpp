// vim: set noexpandtab tabstop=2:

#include <list>
#include "../../splicedAlnUtil.hpp"
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int, char* argv[])
{
	SeqString ref_seq((string(argv[1])));
	SeqSuffixArray ref_SA(ref_seq);

	SeqString query((string(argv[2])));

	AlnSpliceOpt opt;
	opt.word_length = 2;
	opt.word_max_overlap = 0;

	vector<WordPtr> words;
	generate_words(query, words, opt);

	std::list<WordHitPtr> wordHitList;
	collect_wordHits(words, wordHitList, ref_SA);

	printf("word_id\tword_seq\tword_r_seq\tnum_occ\n");
	for(auto iter = words.begin(); iter != words.end(); ++iter)
	{
		cout << (*iter)->id << "\t" << (*iter)->seq << "\t" << (*iter)->r_seq << "\t" << (*iter)->num_occ << endl;
	}

	cout << "\n\n";

	for(auto iter = wordHitList.begin(); iter != wordHitList.end(); ++iter)
	{
		(*iter)->display();
		cout << "\n";
	}
}
