// vim: set noexpandtab tabstop=2:

#include <spliced_aln/Word.hpp>

bool compare_wordsByHitDiagonal(const WordPtr word1, const WordPtr word2)
{
	long diag_1 = word1->ref_pos - word1->query_pos;
	long diag_2 = word2->ref_pos - word2->query_pos;
	return diag_1 < diag_2;	
}

bool compare_wordsByRefPos(const WordPtr word1, const WordPtr word2)
{
	return word1->ref_pos < word2->ref_pos;
}

bool compare_wordsByQueryPos(const WordPtr word1, const WordPtr word2)
{
	return word1->query_pos < word2->query_pos;
}

bool compare_wordsByRefAndStrand(const WordPtr word1, const WordPtr word2)
{
	if (word1->strand != word2->strand)
	{
		return word1->strand < word2->strand;
	}
	else
	{
		return word1->ref_pos < word2->ref_pos;
	}
}

bool check_wordListsColinearity(const std::list<WordPtr>& wordList)
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
