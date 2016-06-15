// vim: set noexpandtab tabstop=2:

#include <spliced_aln/WordHitsGroup.hpp>

using namespace std;

bool compare_wordHitsGroupByScore(const WordHitsGroupPtr group1, const WordHitsGroupPtr group2)
{
  return group1->score < group2->score;
}
