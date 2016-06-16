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
