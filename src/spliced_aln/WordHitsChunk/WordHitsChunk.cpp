// vim: set noexpandtab tabstop=2:

#include <spliced_aln/WordHitsChunk.hpp>

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

//Query need to be decided by strand, whethear is seq or reverse_seq
void WordHitsChunk::extend_inexact(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore, ExtendDirection::Value direction)
{
	//extend on the left
	if(direction != ExtendDirection::right)
	{
		extend_inexact_left(query, ref_SAIndex, stop_atNegativeScore);
	}

	//extend on the right
	if(direction != ExtendDirection::left)
	{
		extend_inexact_right(query, ref_SAIndex, stop_atNegativeScore);
	}
}
