// vim: set noexpandtab tabstop=2:

#include "../../WordHitsGroupUtil.hpp"
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
	AlnSpliceOpt opt;
	opt.min_intron_size = 0;
	opt.min_anchor_size = 0;
	opt.min_exon_size = 0;

	SeqString query = string(argv[1]);
	SeqString ref = string(argv[2]);
	SeqSuffixArray ref_SAIndex(ref);

	WordHitsGroup wordhit_group = WordHitsGroup(0);

	WordHitsChunkPtr tail_chunk = make_shared<WordHitsChunk>(0);
	tail_chunk->start_pos_in_ref = atoi(argv[3]);
	tail_chunk->start_pos_in_query = atoi(argv[4]);
	wordhit_group.wordhitschunks.push_back(tail_chunk);

	int num_backSearch = atoi(argv[5]);

	locate_bridge_by_one_chunk_denovo_upstream(
			tail_chunk
			, wordhit_group.wordhitschunkbridges
			, wordhit_group.wordhitschunks
			, num_backSearch
			, query, ref_SAIndex, opt);

	printf("number of bridge created: %lu\n", wordhit_group.wordhitschunkbridges.size());
	printf("head_chunk info:\n");
	wordhit_group.wordhitschunks.back()->display_pos();
	cout << endl;
	printf("bridge_chunk info:\n");
	for(WordHitsChunkBridgePtr bridge : wordhit_group.wordhitschunkbridges)
	{
		bridge->display();
		cout << endl;
	}
}
