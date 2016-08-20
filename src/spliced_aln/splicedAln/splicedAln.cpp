// vim: set noexpandtab tabstop=3:

#include <spliced_aln/splicedAln.hpp>
#include <spliced_aln/splicedAlnUtil.hpp>
#include <spliced_aln/Word.hpp>
#include <spliced_aln/WordHit.hpp>
#include <vector>

using namespace std;

void splicedAln(const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
  //Generate Word
  vector<WordPtr> wordsVector;
  generate_words(query, wordsVector, opt);
  cout << "Word generated\n" << endl;

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
	 cout << hit->word_id << "\t" << wordsVector[hit->word_id]->seq << "\t" << hit->ref_pos << "\t" << hit->query_pos << endl;
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
	 (*iter)->wordhits.sort(compare_wordHitsByHitDiagonal);
	 (*iter)->group_wordHits_wordChunks(opt, wordsVector.size());
	 cout << "Word hit chunk created\n" << endl;
	 for(auto chunk_iter = (*iter)->wordhitschunks.begin(); chunk_iter != (*iter)->wordhitschunks.end(); ++chunk_iter)
	 {
		bool stop_atNegativeScore = false;
		(*chunk_iter)->extend_inexact(query, ref_SAIndex, stop_atNegativeScore, ExtendDirection::both);
	 }
	 cout << "Word hit chunk extended\n" << endl;

	 //for(auto chunk_iter = (*iter)->wordhitschunks.begin(); chunk_iter != (*iter)->wordhitschunks.end(); ++chunk_iter)
	 //{
	 //  (*chunk_iter)->refine(query, ref_SAIndex, opt);
	 //}

	 //(*iter)->pair_wordHitsChunks(query, ref_SAIndex, opt);
  }
}
