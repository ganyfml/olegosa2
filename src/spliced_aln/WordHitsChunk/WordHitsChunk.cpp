// vim: set noexpandtab tabstop=2:

#include <spliced_aln/WordHitsChunk.hpp>
#include <spliced_aln/aln_global.hpp>

bool compare_wordHitsChunkByRefPos(const WordHitsChunkPtr chunk1, const WordHitsChunkPtr chunk2)
{
	if(chunk1->hit_refPosNonDec == chunk2->hit_refPosNonDec)
	{
		return chunk1->start_pos_in_ref < chunk2->start_pos_in_ref;
	}
	else
	{
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
	end_pos_in_ref = last_hit->ref_pos + word_size - 1;
	start_pos_in_query = first_hit->query_pos;
	end_pos_in_query = last_hit->query_pos + word_size - 1;
	strand = hit_strand;
	is_first_in_bridge = true;
	is_last_in_bridge = true;
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
	const int match_score = 1, mismatch_score = -3, max_diff = 2;

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
	const int match_score = 1, mismatch_score = -3, max_diff = 2;

	int offset_at_max_score = 0, diff_at_max_score = 0;
	int curr_score = 0, diff = 0, max_score = 0;
	for(int i = 0; (i + end_pos_in_query) < query.get_length() && (i + end_pos_in_ref) < ref_SAIndex.seq_length(); ++i)
	{
		if(query[i + end_pos_in_query] == ref_SAIndex.char_at(i + end_pos_in_ref))
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


void WordHitsChunk::align_cleft(const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt)
{
	if(wordHitList.size() < 2) return;

	for(auto first = wordHitList.begin(), second = ++wordHitList.begin(); second != wordHitList.end(); ++first, ++second)
	{
		long ref_cleft_start = (*first)->ref_pos + opt.word_length;
		long ref_cleft_len = (*second)->ref_pos - ref_cleft_start;

		long query_cleft_start = (*first)->query_pos + opt.word_length;
		long query_cleft_len = (*second)->query_pos - query_cleft_start;

		if (ref_cleft_len <= 0 && query_cleft_len <= 0 && query_cleft_len == ref_cleft_len )
		{
			continue;
		}
		else if (ref_cleft_len <= 0 && query_cleft_len > ref_cleft_len )
		{
			this->gapMM.num_gapOpenRef += 1;
			this->gapMM.num_gapExtRef += (query_cleft_len - ref_cleft_len - 1);
			continue;
		}
		else if (query_cleft_len <= 0 && ref_cleft_len > query_cleft_len)
		{
			this->gapMM.num_gapOpenQuery += 1;
			this->gapMM.num_gapExtQuery += (ref_cleft_len- query_cleft_len - 1);
			continue;
		}

		SeqString query_part = query.get_infix(query_cleft_start, query_cleft_start + query_cleft_len - 1);
		SeqString ref_part = ref_SAIndex.get_infixSeq(ref_cleft_start, ref_cleft_start + ref_cleft_len - 1);
		std::cout << "cleft: " << std::endl;
		std::cout << "query: " << query_part << std::endl;
		std::cout << "ref: " << ref_part << std::endl;
		GapAndMM gap_mm;
		aln_global(ref_part, query_part, gap_mm);
		this->gapMM += gap_mm;
	}
}
