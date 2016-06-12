// vim: set noexpandtab tabstop=2:

#include <list>
#include <vector>
#include <iostream>
#include "../../../splicedAlnUtil.hpp"
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int, char* argv[])
{
	//Construct ref_SA
	SeqString ref_seq((string(argv[1])));
	SeqSuffixArray ref_SA(ref_seq);

	//Construct word
	SeqString word_seq (argv[2]);
	int word_id = 0;
	long word_query_pos = 1;
	long word_r_query_pos = 99;
	WordPtr word = make_shared<Word>(word_id, word_query_pos, word_r_query_pos, word_seq);
	vector<WordPtr> words;
	words.push_back(word);

	//Construct return list
	list<WordHitPtr> wordHitList;
	//Construct word_search_opt, make it default which only allow exact match
	alnNonspliceOpt word_search_opt;

	//Test function
	bool revcomp = atoi(argv[3]);
	collect_wordHits(words, wordHitList, ref_SA, revcomp, word_search_opt);

	printf("word_id\tref_pos\tquery_pos\n");
	for(auto iter = wordHitList.begin(); iter != wordHitList.end(); ++iter)
	{
		printf("%d\t%lu\t%lu\n", (*iter)->word_id, (*iter)->ref_pos, (*iter)->query_pos);
		cout << "\n\n";
	}
}
