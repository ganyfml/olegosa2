// vim: set noexpandtab tabstop=2:

#include <spliced_aln/WordHitsGroupUtil.hpp>

using namespace std;

Strand::Value determin_strand_by_canonical_spliceSite(const SeqSuffixArray& ref_SAIndex, long donor_pos, long acceptor_pos)
{
	if(ref_SAIndex.char_at(donor_pos) == 'G' && ref_SAIndex.char_at(donor_pos + 1) == 'T'
			&& ref_SAIndex.char_at(acceptor_pos - 1) == 'A' && ref_SAIndex.char_at(acceptor_pos) == 'G')
	{
		return Strand::forward;
	}
	else if(ref_SAIndex.char_at(donor_pos) == 'C' && ref_SAIndex.char_at(donor_pos + 1) == 'T'
			&& ref_SAIndex.char_at(acceptor_pos - 1) == 'A' && ref_SAIndex.char_at(acceptor_pos) == 'C')
	{
		return Strand::reverse;
	}
	return Strand::none_decide;
}

std::pair<int, int> cal_two_wordchunks_backsearch_area_diff(const WordHitsChunkPtr head_chunk, const WordHitsChunkPtr tail_chunk, const SeqString query, const SeqSuffixArray& ref_SAIndex, int num_backSearch)
{
	int head_chunk_diff = 0;
	int tail_chunk_diff = 0;
	for(int i = 0; i <= num_backSearch; ++i)
	{
		long head_chunk_queryEnd = head_chunk->end_pos_in_query - i;
		long head_chunk_refEnd = head_chunk->end_pos_in_ref - i;
		if(query[head_chunk_queryEnd] != ref_SAIndex.char_at(head_chunk_refEnd))
		{
			++head_chunk_diff;
		}

		long tail_chunk_refEnd = tail_chunk->start_pos_in_ref + i;
		long tail_chunk_queryEnd = tail_chunk->start_pos_in_query + i;
		if(query[tail_chunk_queryEnd] != ref_SAIndex.char_at(tail_chunk_refEnd))
		{
			++tail_chunk_diff;
		}
	}
	return std::pair<int, int>(head_chunk_diff, tail_chunk_diff);
}


//BACKUP
/*
	 void cal_two_wordChunks_adjust_diff(const WordHitsChunkPtr head_chunk, const WordHitsChunkPtr tail_chunk, vector<int>& head_chunk_adjust_diff, vector<int>& tail_chunk_adjust_diff, const SeqString query, const SeqSuffixArray& ref_SAIndex, int num_backSearch)
	 {
	 head_chunk_adjust_diff = vector<int>(num_backSearch + 1);
	 tail_chunk_adjust_diff = vector<int>(num_backSearch + 1);
	 int head_chunk_diff = 0;
	 int tail_chunk_diff = 0;
	 for(int i = 0; i < num_backSearch + 1; ++i)
	 {
	 long head_chunk_queryEnd = head_chunk->end_pos_in_query - i;
	 if(query[head_chunk_queryEnd] != ref_SAIndex.char_at(head_chunk_refEnd))
	 {
	 ++head_chunk_diff;
	 }
	 head_chunk_adjust_diff[i] = head_chunk_diff;

	 long tail_chunk_refEnd = tail_chunk->start_pos_in_ref + i;
	 long tail_chunk_queryEnd = tail_chunk->start_pos_in_query + i;
	 if(query[tail_chunk_queryEnd] != ref_SAIndex.char_at(tail_chunk_refEnd))
	 {
	 ++tail_chunk_diff;
	 }
	 tail_chunk_adjust_diff[i] = tail_chunk_diff;
	 }
	 }*/
