// vim: set noexpandtab tabstop=2:

#include <spliced_aln/WordHitsChunk.hpp>

bool compare_wordHitsChunkByRefPos(const WordHitsChunkPtr chunk1, const WordHitsChunkPtr chunk2)
{
	if(chunk1->hit_refPosNonDec != chunk2->hit_refPosNonDec)
	{
		return chunk1->hit_refPosNonDec > chunk2->hit_refPosNonDec;
	}
	else
	{
		return chunk1->refStart_pos < chunk2->refStart_pos;
	}
}

void WordHitsChunk::evaluate(int word_size, int hit_strand)
{
	wordHitList.sort(compare_wordHitsByQueryPos);
	hit_refPosNonDec = is_refPos_nondecreasing(wordHitList);

	coverage = double(wordHitList.size()) / (wordHitList.back()->word_id - wordHitList.front()->word_id + 1);

	WordHitPtr first_hit = wordHitList.front();
	WordHitPtr last_hit = wordHitList.back();

	refStart_pos = first_hit->ref_pos;
	refEnd_pos = last_hit->ref_pos + word_size;
	queryStart_pos = first_hit->query_pos;
	queryEnd_pos = last_hit->query_pos + word_size;
	strand = hit_strand;
}
