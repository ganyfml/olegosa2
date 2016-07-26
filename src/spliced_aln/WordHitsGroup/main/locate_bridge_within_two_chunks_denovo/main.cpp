// vim: set noexpandtab tabstop=2:

#include "../../WordHitsGroup.hpp"
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
	int head_chunk_id = 0;
	WordHitsChunkPtr head_chunk = make_shared<WordHitsChunk>(head_chunk_id);
	head_chunk->end_pos_in_ref = atoi(argv[1]);
	head_chunk->end_pos_in_query = atoi(argv[2]);

	int tail_chunk_id = 1;
	WordHitsChunkPtr tail_chunk = make_shared<WordHitsChunk>(tail_chunk_id);
	tail_chunk->start_pos_in_ref = atoi(argv[3]);
	tail_chunk->start_pos_in_query = atoi(argv[4]);

	int num_backSearch = atoi(argv[5]);

	int gap_length = tail_chunk->start_pos_in_query - head_chunk->end_pos_in_query - 1 + 2 * num_backSearch;
	long min_headChunk_refEnd = head_chunk->end_pos_in_ref - num_backSearch;
	long max_headChunk_refEnd = min_headChunk_refEnd + gap_length - 1;

	AlnSpliceOpt opt;
	opt.min_intron_size = 1;
	opt.min_anchor_size = 1;

	SeqString query = string(argv[6]);
	SeqString ref = string(argv[7]);
	SeqSuffixArray ref_SAIndex(ref);

	int group_id = 0;
	WordHitsGroup wordhit_group = WordHitsGroup(group_id);
	wordhit_group.wordhitschunks.push_back(head_chunk);
	wordhit_group.wordhitschunks.push_back(tail_chunk);
	wordhit_group.locate_bridge_within_two_chunks_denovo(head_chunk, tail_chunk, min_headChunk_refEnd, max_headChunk_refEnd, gap_length, num_backSearch, query, ref_SAIndex, opt);
	
	cout << wordhit_group.wordhitschunkbridges.size() << endl;
	wordhit_group.wordhitschunkbridges.front()->display();
}
