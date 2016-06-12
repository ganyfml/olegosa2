// vim: set noexpandtab tabstop=2:

#include <spliced_aln/WordHit.hpp>

bool compare_wordHitsByHitDiagonal(const WordHitPtr word_hit1, const WordHitPtr word_hit2)
{
	long diag_1 = word_hit1->ref_pos - word_hit1->query_pos;
	long diag_2 = word_hit2->ref_pos - word_hit2->query_pos;
	return diag_1 < diag_2;	
}

bool compare_wordHitsByRefPos(const WordHitPtr word_hit1, const WordHitPtr word_hit2)
{
	return word_hit1->ref_pos < word_hit2->ref_pos;
}

bool compare_wordHitsByQueryPos(const WordHitPtr word_hit1, const WordHitPtr word_hit2)
{
	return word_hit1->query_pos < word_hit2->query_pos;
}

bool is_collinear(const std::list<WordHitPtr>& wordList)
{
	bool is_colinear = true;
	for(auto first = wordList.begin(), second = ++wordList.begin()
			; second != wordList.end()
			; ++first, ++second)
	{
		if((*first)->ref_pos > (*second)->ref_pos)
		{
			is_colinear = false;
			break;
		}
	}
	return is_colinear;
}
