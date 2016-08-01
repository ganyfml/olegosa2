// vim: set noexpandtab tabstop=2:

#include "../../WordHitsGroupUtil.hpp"
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
	alnNonspliceOpt anchor_search_opt;

	SeqString ref = string(argv[1]);
	SeqSuffixArray ref_SAIndex(ref);

	SeqString anchor_seq = string(argv[2]);
	long hit_left_bound = atoi(argv[3]);
	long hit_right_bound = atoi(argv[4]);

	list<long> anchor_hit_list{};
	collect_anchor_hits_within_bound(anchor_seq, anchor_hit_list, ref_SAIndex, hit_left_bound, hit_right_bound, anchor_search_opt);
	printf("%ld anchors found!\n", anchor_hit_list.size());
	for(long hit : anchor_hit_list)
	{
		printf("anchor found in: %ld\n", hit);
	}
}
