// vim: set noexpandtab tabstop=3:

#include<iostream>
#include"../../WordHitsGroup.hpp"

using namespace std;

int main()
{
  WordHitsChunkPtr head_chunk = make_shared<WordHitsChunk>(1);
  WordHitsChunkPtr tail_chunk = make_shared<WordHitsChunk>(1);

  head_chunk->refEnd_pos = 5;
  head_chunk->queryEnd_pos = 3;
  tail_chunk->refStart_pos = 10;
  tail_chunk->queryStart_pos = 8;

  SeqString query("GGATAAAATAAGAG");
  SeqString ref("AAAAATAAAATAAAAA");
  SeqSuffixArray ref_SA(ref);

  vector<int> head_chunk_adjust_diff;
  vector<int> tail_chunk_adjust_diff;
  int num_backSearch = 3;
  cal_wordChunk_adjust_diff(head_chunk, tail_chunk, head_chunk_adjust_diff, tail_chunk_adjust_diff, query, ref_SA, num_backSearch);

  cout << "head adjust diff: " << endl;
  for(int i = 0; i < num_backSearch + 1; ++i)
  {
	 cout << head_chunk_adjust_diff[i] << " " << endl;
  }
  cout << endl;

  cout << "tail adjust diff: " << endl;
  for(int i = 0; i < num_backSearch + 1; ++i)
  {
	 cout << tail_chunk_adjust_diff[i] << " " << endl;
  }
  cout << endl;
}
