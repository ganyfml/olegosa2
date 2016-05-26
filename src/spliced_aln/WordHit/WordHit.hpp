// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/SeqString.hpp>
#include <list>
#include <iostream>

struct WordHit
{
	int word_id;
	int strand;
	long query_pos;
	long ref_pos;

	WordHit(int id, int strand)
		: strand(strand), query_pos(0), ref_pos(0)
	{
		//DEBUG
		//word_id = strand ? -id : id;
		word_id = id;
		//END
	}

	void display()
	{
		std::cout << "Word ID: " << word_id << ", With strand: " << strand << std::endl;
		std::cout << "query_pos: " << query_pos << ", ref_pos: " << ref_pos << std::endl;
	}
};

typedef std::shared_ptr<WordHit> WordHitPtr;

bool compare_wordHitsByHitDiagonal(const WordHitPtr word_hit1, const WordHitPtr word_hit2);
bool compare_wordHitsByRefPos(const WordHitPtr word_hit1, const WordHitPtr word_hit2);
bool compare_wordHitsByQueryPos(const WordHitPtr word_hit1, const WordHitPtr word_hit2);
bool compare_wordHitsByRefAndStrand(const WordHitPtr word_hit1, const WordHitPtr word_hit2);
bool check_wordHitListColinearity(const std::list<WordHitPtr>& wordList_);
