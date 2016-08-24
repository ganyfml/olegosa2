// vim: set noexpandtab tabstop=3:

#include <spliced_aln/splicedAln.hpp>
#include <spliced_aln/splicedAlnUtil.hpp>
#include <spliced_aln/Word.hpp>
#include <spliced_aln/WordHit.hpp>
#include <spliced_aln/WordHitsGroupUtil.hpp>
#include <vector>

using namespace std;

void splicedAln(const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
	//Generate Word
	vector<WordPtr> wordsVector;
	generate_words(query, wordsVector, opt);
	cout << "Word generated\n" << endl;

	for(auto word : wordsVector)
	{
		word->display();
		cout << endl;
	}

	//Generate WordHit
	list<WordHitPtr> wordHitsList;
	alnNonspliceOpt word_search_opt;

	//Rev_comp = false
	bool rev_comp = false;
	collect_wordHits(wordsVector, wordHitsList, ref_SAIndex, rev_comp, word_search_opt);
	wordHitsList.sort(compare_wordHitsByRefPos);
	cout << "Word hits collected and sorted\n" << endl;

	for(WordHitPtr hit : wordHitsList)
	{
		hit->display();
	}

	//Use WordHits to form WordHitsGroup
	list<WordHitsGroupPtr> wordHitsGroupList;
	group_wordHits_wordHitsGroup(wordHitsList, wordHitsGroupList, opt.max_intron_size);
	cout << "Word hit group created\n" << endl;

	//for(WordHitsGroupPtr group : wordHitsGroupList)
	//{
	//  group->score = calculate_wordhitsChunk_score(group, wordsVector, ref_SAIndex.seq_length(), wordsVector.size());
	//  group->display();
	//}

	wordHitsGroupList.sort(compare_wordHitsGroupByScore);

	//For each WordHitsGroup
	//1. group WordHits into WordHitsChunks
	//2. Extend and refine those wordHitsChunks
	//3. pair those wordHitsChunks and form wordHitsBridge

	for(auto iter = wordHitsGroupList.begin(); iter != wordHitsGroupList.end(); ++iter)
	{
		printf("/////////////////////////////////\n");
		(*iter)->wordhits.sort(compare_wordHitsByHitDiagonal);
		(*iter)->group_wordHits_wordChunks(opt, wordsVector.size());
		cout << "Word hit chunk created\n" << endl;
		for(auto chunk_iter = (*iter)->wordhitschunks.begin(); chunk_iter != (*iter)->wordhitschunks.end(); ++chunk_iter)
		{
			bool stop_atNegativeScore = false;
			(*chunk_iter)->summarize(opt.word_length, Strand::forward);
			(*chunk_iter)->display();
			cout << "////" << endl;
			(*chunk_iter)->extend_inexact(query, ref_SAIndex, stop_atNegativeScore, ExtendDirection::both);
			cout << "//" << endl;
			(*chunk_iter)->display();
			cout << "\\\\" << endl;
		}

		cout << "Word hit chunk extended\n" << endl;

		//for(auto chunk_iter = (*iter)->wordhitschunks.begin(); chunk_iter != (*iter)->wordhitschunks.end(); ++chunk_iter)
		//{
		//  (*chunk_iter)->refine(query, ref_SAIndex, opt);
		//}

		(*iter)->pair_wordHitsChunks(query, ref_SAIndex, opt);
		printf("Word hit chunk paired, %ld bridges created\n", (*iter)->wordhitschunkbridges.size());

		for(auto bridge_iter = (*iter)->wordhitschunkbridges.begin(); bridge_iter != (*iter)->wordhitschunkbridges.end(); ++bridge_iter)
		{
			(*bridge_iter)->display();
		}

		list<WordHitsChunkBridgeChainPtr> results;
		concat_bridges((*iter)->wordhitschunkbridges, results, query.get_length(), true);
		printf("\nbridge concated, %ld chain creaded\n", results.size());
		for(auto chain_iter = results.begin(); chain_iter != results.end(); ++chain_iter)
		{
			(*chain_iter)->display();
		}
	}
}
