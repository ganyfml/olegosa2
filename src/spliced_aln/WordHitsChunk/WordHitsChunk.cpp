// vim: set noexpandtab tabstop=2:

#include <spliced_aln/WordHitsChunk.hpp>

bool compare_wordHitsChunkByRefPos(const WordHitsChunkPtr chunk1, const WordHitsChunkPtr chunk2)
{
	if(chunk1->hit_refPosNonDec == chunk2->hit_refPosNonDec)
	{
		return chunk1->start_pos_in_ref < chunk2->start_pos_in_ref;
	}
	else
	{
		std::cout << "Get here!\n";
		return chunk1->hit_refPosNonDec > chunk2->hit_refPosNonDec;
	}
}

void WordHitsChunk::summarize(int word_size, Strand::Value hit_strand)
{
	wordHitList.sort(compare_wordHitsByQueryPos);
	hit_refPosNonDec = is_refPos_nondecreasing(wordHitList);

	coverage = double(wordHitList.size()) / (wordHitList.back()->word_id - wordHitList.front()->word_id + 1);

	WordHitPtr first_hit = wordHitList.front();
	WordHitPtr last_hit = wordHitList.back();

	start_pos_in_ref = first_hit->ref_pos;
	end_pos_in_ref = last_hit->ref_pos + word_size;
	start_pos_in_query = first_hit->query_pos;
	end_pos_in_query = last_hit->query_pos + word_size;
	strand = hit_strand;
}

void WordHitsChunk::extend_inexact(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore, ExtendDirection::Value direction)
{
	if(direction & ExtendDirection::right)
	{
		extend_inexact_left(query, ref_SAIndex, stop_atNegativeScore);
	}

	if(direction & ExtendDirection::left)
	{
		extend_inexact_right(query, ref_SAIndex, stop_atNegativeScore);
	}
}

void WordHitsChunk::extend_inexact_left(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore)
{
	const int match_score = 3, mismatch_score = -1, max_diff = 2;

	int offset_at_max_score = 0, diff_at_max_score = 0;
	int curr_score = 0, diff = 0, max_score = 0;
	for(int i = 0; i <= start_pos_in_query && i <= start_pos_in_ref; ++i)
	{
		if(query[start_pos_in_query - i] == ref_SAIndex.char_at(start_pos_in_ref - i))
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
		else if(curr_score > max_score || start_pos_in_query - i == 0)
		{
			max_score = curr_score;
			offset_at_max_score = i;
			diff_at_max_score = diff;
		}
	}

	start_pos_in_query -= offset_at_max_score;
	start_pos_in_ref -= offset_at_max_score;
	gapMM.num_mismatch += diff_at_max_score;	
}

void WordHitsChunk::extend_inexact_right(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore)
{
	const int match_score = 3, mismatch_score = -1, max_diff = 2;

	int offset_at_max_score = 0, diff_at_max_score = 0;
	int curr_score = 0, diff = 0, max_score = 0;
	for(int i = 0; i < (query.get_length() - end_pos_in_query) && i < (ref_SAIndex.seq_length() - end_pos_in_ref); ++i)
	{
		if(query[end_pos_in_query + i] == ref_SAIndex.char_at(end_pos_in_ref + i))
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

		if(curr_score > max_score || ((end_pos_in_query + i + 1) == query.get_length()) )
		{
			max_score = curr_score;
			offset_at_max_score = i;
			diff_at_max_score = diff;
		}
	}

	end_pos_in_query += offset_at_max_score;
	end_pos_in_ref += offset_at_max_score;
	gapMM.num_mismatch += diff_at_max_score;
}
