// vim: set noexpandtab tabstop=2:

#include <list>
#include "../../splicedAlnUtil.hpp"
#include <nonspliced_aln/nonsplicedAln.hpp>
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int, char* argv[])
{
	SeqString ref_seq((string(argv[1])));
	SeqSuffixArray ref_SA(ref_seq);
	SeqString query(argv[2]);

	AlnSpliceOpt opt;
	opt.word_length = 2;
	opt.word_max_overlap = 0;

	vector<WordPtr> words;
	generate_words(query, words, opt);
	cout << "num of words generated: " << words.size() << endl;
	words[0]->display();

	std::queue<AlnResult> word_hit_result;
	alnNonspliceOpt word_search_opt;
	nonsplicedAln(words[0]->seq, word_hit_result, ref_SA, word_search_opt);

	printf("\n\nnumber of hit: %lu\n", word_hit_result.size());
	cout << "Hit seq: " << ref_SA.getSeq_bySAIndex(word_hit_result.front().SA_index_low, word_hit_result.front().seq_length) << ", with SA index high: " << word_hit_result.front().SA_index_high << ", low: " << word_hit_result.front().SA_index_low << endl;

	int strand = 0;
	std::list<WordHitPtr> word_hits_list;
	collect_wordHitsByAlnResult(word_hit_result, word_hits_list, ref_SA, words[0], strand);

	printf("\n\nnum of wordHit generated: %d\n", word_hits_list.size());
	for(auto iter = word_hits_list.begin(); iter != word_hits_list.end(); ++iter)
	{
		(*iter)->display();
		printf("\n");
	}
}
