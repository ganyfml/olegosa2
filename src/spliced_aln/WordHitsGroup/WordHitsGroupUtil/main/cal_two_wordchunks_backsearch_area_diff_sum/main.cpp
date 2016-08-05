// vim: set noexpandtab tabstop=2:

#include "../../WordHitsGroupUtil.hpp"
#include <map>
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
	SeqString ref = string(argv[1]);
	SeqSuffixArray ref_SAIndex(ref);

	SeqString query = string(argv[2]);

	int head_chunk_id = 0;
	WordHitsChunkPtr head_chunk = make_shared<WordHitsChunk>(head_chunk_id);
	head_chunk->end_pos_in_ref = atoi(argv[3]);
	head_chunk->end_pos_in_query = atoi(argv[4]);
	printf("head_chunk: end pos in ref: %ld, end pos in query: %d\n", head_chunk->end_pos_in_ref, head_chunk->end_pos_in_query);

	int tail_chunk_id = 0;
	WordHitsChunkPtr tail_chunk = make_shared<WordHitsChunk>(tail_chunk_id);
	tail_chunk->start_pos_in_ref = atoi(argv[5]);
	tail_chunk->start_pos_in_query = atoi(argv[6]);
	printf("tail_chunk: start pos in ref: %ld, start pos in query: %d\n", tail_chunk->start_pos_in_ref, tail_chunk->start_pos_in_query);

	int num_backSearch = 1;
	int diff_sum = cal_two_wordchunks_backsearch_area_diff_sum(head_chunk, tail_chunk, query, ref_SAIndex, num_backSearch);
	printf("head_chunk and tail_chunk diff sum: %d\n", diff_sum);
}
