// vim: set noexpandtab tabstop=3:

#include <list>
#include "../../WordHitsGroup.hpp"
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqString.hpp>
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
  int group1_id = 0;
  WordHitsGroupPtr group1 = make_shared<WordHitsGroup>(group1_id);
  group1->score = atoi(argv[1]);
  int group2_id = 1;
  WordHitsGroupPtr group2 = make_shared<WordHitsGroup>(group2_id);
  group2->score = atoi(argv[2]);
  printf("%d\n", compare_wordHitsGroupByScore(group1, group2));
}
