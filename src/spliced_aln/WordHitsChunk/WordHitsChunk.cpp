// vim: set noexpandtab tabstop=2:

#include <spliced_aln/WordHitsChunk.hpp>
#include <spliced_aln/aln_global.hpp>

void WordHitsChunk::extend_inexact_left(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore)
{
	const int match_score = 3;
	const int mismatch_score = -1;
	const int max_diff = 2;

	long index = 1;
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

void WordHitsChunk::refine(const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
	if(wordHitList.size() < 2) return;

	for(auto first = wordHitList.begin(), second = ++wordHitList.begin(); second != wordHitList.end(); ++first, ++second)
	{
		long ref_start = (*first)->ref_pos + opt.word_length;
		long ref_len = (*second)->ref_pos - ref_start;

		long query_start = (*first)->query_pos + opt.word_length;
		long query_len = (*second)->query_pos - query_start;

		if (ref_len <= 0 && query_len <= 0 && query_len == ref_len )
		{
			continue;
		}
		else if (ref_len <= 0 && query_len > ref_len )
		{
			this->gapMM.num_gapOpenRef += 1;
			this->gapMM.num_gapExtRef += (query_len- ref_len - 1);
			continue;
		}
		else if (query_len <= 0 && ref_len > query_len)
		{
			this->gapMM.num_gapOpenQuery += 1;
			this->gapMM.num_gapExtQuery += (ref_len- query_len - 1);
			continue;
		}

		SeqString query_part = query.get_infix(query_start, query_start + query_len);
		SeqString ref_part = ref_SAIndex.get_infixSeq(ref_start, ref_start + ref_len);
		GapAndMM gap_mm;
		aln_global(ref_part, query_part, gap_mm);
		this->gapMM += gap_mm;
	}
}
