// vim: set noexpandtab tabstop=3:

#include <list>
#include "../../WordHitsGroup.hpp"
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqString.hpp>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  int word1_hit1_wordID = 0;
  int word1_hit1_strand= 0;
  WordHit hit1(word1_hit1_wordID, word1_hit1_strand);
  WordHitPtr word1_hit1_ptr = make_shared<WordHit>(hit1);

  int word1_hit2_wordID = 0;
  int word1_hit2_strand= 0;
  WordHit hit2(word1_hit2_wordID, word1_hit2_strand);
  WordHitPtr word1_hit2_ptr = make_shared<WordHit>(hit2);

  int word2_hit1_wordID = 1;
  int word2_hit1_strand= 0;
  WordHit hit3(word2_hit1_wordID, word2_hit1_strand);
  WordHitPtr word2_hit1_ptr = make_shared<WordHit>(hit3);

  int word1_id = 0;
  int word1_len = 3;
  int word1_query_pos = 5;
  int word1_r_query_pos = 95;
  SeqString word1_seq("ACG");
  SeqString word1_r_seq("CGT");
  WordPtr word1ptr = make_shared<Word>(word1_id, word1_len, word1_query_pos, word1_r_query_pos, word1_seq, word1_r_seq);
  word1ptr->num_occ = 2;

  int word2_id = 1;
  int word2_len = 3;
  int word2_query_pos = 7;
  int word2_r_query_pos = 93;
  SeqString word2_seq("AAG");
  SeqString word2_r_seq("CCT");
  WordPtr word2ptr = make_shared<Word>(word2_id, word2_len, word2_query_pos, word2_r_query_pos, word2_seq, word2_r_seq);
  word2ptr->num_occ = 1;

  int group_id = 0;
  WordHitsGroupPtr test_group = make_shared<WordHitsGroup>(group_id);
  test_group->wordhits.push_back(word1_hit1_ptr);
  test_group->wordhits.push_back(word1_hit2_ptr);
  test_group->wordhits.push_back(word2_hit1_ptr);

  vector<WordPtr> words;
  words.push_back(word1ptr);
  words.push_back(word2ptr);

  int num_words = 2;
  int ref_len = 100;
  cout << calculate_wordhitsChunk_score(test_group, words, ref_len, num_words) << endl;
}
