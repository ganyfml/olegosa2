// vim: set noexpandtab tabstop=3:

#include<iostream>
#include"../../WordHitsGroup.hpp"

using namespace std;

int main(int, char* argv[])
{
  WordHitsChunkPtr head_chunk = make_shared<WordHitsChunk>(1);
  WordHitsChunkPtr tail_chunk = make_shared<WordHitsChunk>(1);

  head_chunk->strand = atoi(argv[1]);
  tail_chunk->strand = atoi(argv[2]);

  head_chunk->refEnd_pos = 1;
  tail_chunk->refStart_pos = 2;

  GapAndMM head_gap(1, 0, 0, 0, 0);
  GapAndMM tail_gap(2, 0, 0, 0, 0);
  head_chunk->gapMM = head_gap;
  tail_chunk->gapMM = tail_gap;

  head_chunk->colinearity = true;
  tail_chunk->colinearity = true;

  WordHitPtr head_hit = make_shared<WordHit>(0, 0);
  WordHitPtr tail_hit = make_shared<WordHit>(1, 0);
  head_chunk->wordHitList.push_back(head_hit);
  tail_chunk->wordHitList.push_back(tail_hit);

  AlnSpliceOpt opt;
  opt.wordChunk_max_diff = 3;

  cout << "Can pair? " << can_pair(head_chunk, tail_chunk, opt) << endl;
}
