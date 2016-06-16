// vim: set noexpandtab tabstop=3:

#include <list>
#include "../../../splicedAlnUtil.hpp"
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int argc, char* argv[])
{
	list<WordHitPtr> hits;

	for(int i = 0; i < argc - 1; ++i)
	{
		WordHitPtr hit = make_shared<WordHit>(atoi(argv[i+1]));
		hit->ref_pos = atoi(argv[i+1]);
		hits.push_back(hit);
	}

	list<WordHitsGroupPtr> groups;
	int max_intro_size = 100;
	group_wordHits_wordHitsGroup(hits, groups, max_intro_size);

	for(auto iter = groups.begin(); iter != groups.end(); ++iter)
	{
		(*iter)->display();
	}
}
