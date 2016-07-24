// vim: set noexpandtab tabstop=2:

#include <spliced_aln/WordHitsChunk.hpp>

bool compare_wordHitsChunkByRefPos(const WordHitsChunkPtr chunk1, const WordHitsChunkPtr chunk2)
{
	if(chunk1->hit_refPosNonDec == chunk2->hit_refPosNonDec)
	{
		return chunk1->refStart_pos < chunk2->refStart_pos;
	}
	else
	{
		std::cout << "Get here!\n";
		return chunk1->hit_refPosNonDec > chunk2->hit_refPosNonDec;
	}
}

void WordHitsChunk::evaluate(int word_size, Strand::Value hit_strand)
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

void WordHitsChunk::extend_inexact(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore, ExtendDirection::Value direction)
{
	if(direction != ExtendDirection::right)
	{
		extend_inexact_left(query, ref_SAIndex, stop_atNegativeScore);
	}

	if(direction != ExtendDirection::left)
	{
		extend_inexact_right(query, ref_SAIndex, stop_atNegativeScore);
	}
}

void WordHitsChunk::extend_inexact_left(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore)
{
	const int match_score = 3;
	const int mismatch_score = -1;
	const int max_diff = 2;

	long index = 0;
	int end = 0;
	int curr_score = 0;
	int max_score = 0;
	int diff = 0;
	int min_diff = 0;

	while((queryStart_pos - index) >= 0
			&& (refStart_pos - index) >= 0)
	{
		if(query[queryStart_pos - index] == ref_SAIndex.char_at(refStart_pos - index))
		{
			curr_score += match_score;
		}
		else
		{
			curr_score += mismatch_score;
			++diff;
			if(diff > max_diff)
			{
				break;
			}
		}

		if(stop_atNegativeScore && curr_score < 0)
		{
			break;
		}
		else if(curr_score > max_score || index == queryStart_pos)
		{
			max_score = curr_score;
			end = index;
			min_diff = diff;
		}
		++index;
	}

	queryStart_pos -= end;
	refStart_pos -= end;
	gapMM.num_mismatch += min_diff;	
}

void WordHitsChunk::extend_inexact_right(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore)
{
	const int match_score = 3;
	const int mismatch_score = -1;
	const int max_diff = 2;

	long index = 0;
	int end = 0;
	int score = 0;
	int max_score = 0;
	int diff = 0;
	int min_diff = 0;

	while((queryEnd_pos + index) < query.get_length()
			&& (refEnd_pos + index) < ref_SAIndex.seq_length())
	{
		if(query[queryEnd_pos+ index] == ref_SAIndex.char_at(refEnd_pos + index))
		{
			score += match_score;
		}
		else
		{
			score += mismatch_score;
			++diff;
			if(diff > max_diff)
			{
				break;
			}
		}

		if(stop_atNegativeScore && score < 0)
		{
			break;
		}

		if(score > max_score || ((queryEnd_pos + index + 1) == query.get_length()) )
		{
			max_score = score;
			end = index;
			min_diff = diff;
		}
		++index;
	}

	queryEnd_pos += end;
	refEnd_pos += end;
	gapMM.num_mismatch += min_diff;
}
