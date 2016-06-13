// vim: set noexpandtab tabstop=3:

#include <list>
#include "../../splicedAlnUtil.hpp"
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int, char* argv[])
{
  int hit1_id = 1;
  WordHit hit1(hit1_id);
  hit1.ref_pos = atoi(argv[1]);
  WordHitPtr hit1_ptr = make_shared<WordHit>(hit1);

  int hit2_id = 2;
  WordHit hit2(hit2_id);
  hit2.ref_pos = atoi(argv[2]);
  WordHitPtr hit2_ptr = make_shared<WordHit>(hit2);

  int hit3_id = 3;
  WordHit hit3(hit3_id);
  hit3.ref_pos = atoi(argv[3]);
  WordHitPtr hit3_ptr = make_shared<WordHit>(hit3);

  list<WordHitPtr> hits;
  hits.push_back(hit1_ptr);
  hits.push_back(hit2_ptr);
  hits.push_back(hit3_ptr);

  list<WordHitsGroupPtr> groups;
  int max_intro_size = 100;
  group_wordHits_wordHitsGroup(hits, groups, max_intro_size);

  for(auto iter = groups.begin(); iter != groups.end(); ++iter)
  {
	 (*iter)->display();
  }
}
