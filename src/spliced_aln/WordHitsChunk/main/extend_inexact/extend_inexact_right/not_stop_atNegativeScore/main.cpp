// vim: set noexpandtab tabstop=3:

#include <iostream>
#include "../../../../WordHitsChunk.hpp"

using namespace std;

int main(int, char** argc)
{
  SeqString query = string("TTTTTTTTTTTTT");
  SeqString ref = string(string("GGGTGTTGTG"));
  SeqSuffixArray ref_SAIndex(ref);

  int word_hit_id = 0;
  int hit_strand = 0;
  WordHitPtr hit_test = make_shared<WordHit>(word_hit_id, hit_strand);
  hit_test->query_pos = 5;
  hit_test->ref_pos = 5;

  int wordHitChunkID = 0;
  WordHitsChunkPtr chunk = make_shared<WordHitsChunk>(wordHitChunkID);
  chunk->wordHitList.push_back(hit_test);
  chunk->refStart_pos = 5;
  chunk->refEnd_pos = 7;
  chunk->queryStart_pos = 5;
  chunk->queryEnd_pos = 7;

  bool stop_atNegativeScore = false;
  chunk->extend_inexact_right(query, ref_SAIndex, stop_atNegativeScore);
  chunk->display();
}
