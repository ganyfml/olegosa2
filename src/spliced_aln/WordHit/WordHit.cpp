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

bool compare_WordHitsByQueryPos(const WordHitPtr word_hit1, const WordHitPtr word_hit2)
{
	return word_hit1->query_pos < word_hit2->query_pos;
}

bool compare_wordHitsByRefAndStrand(const WordHitPtr word_hit1, const WordHitPtr word_hit2)
{
	if (word_hit1->strand != word_hit2->strand)
	{
		return word_hit1->strand < word_hit2->strand;
	}
	else
	{
		return word_hit1->ref_pos < word_hit2->ref_pos;
	}
}

bool check_wordHitListColinearity(const std::list<WordHitPtr>& wordList)
{
	bool isColinear = true;
	for(auto first = wordList.begin(), second = ++wordList.begin();
			second != wordList.end();
			++first, ++second)
	{
		if((*first)->ref_pos > (*second)->ref_pos)
		{
			isColinear = false;
			break;
		}
	}
	return isColinear;
}
