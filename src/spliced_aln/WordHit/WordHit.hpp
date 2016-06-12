// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/SeqString.hpp>
#include <list>
#include <iostream>

struct WordHit
{
	int word_id;
	long query_pos;
	long ref_pos;

	WordHit(int id)
		: query_pos(0), ref_pos(0)
	{
		word_id = id;
	}

	void display()
	{
		std::cout << "Word ID: " << word_id << std::endl;
		std::cout << "query_pos: " << query_pos << ", ref_pos: " << ref_pos << std::endl;
	}
};

typedef std::shared_ptr<WordHit> WordHitPtr;

bool compare_wordHitsByHitDiagonal(const WordHitPtr word_hit1, const WordHitPtr word_hit2);
bool compare_wordHitsByRefPos(const WordHitPtr word_hit1, const WordHitPtr word_hit2);
bool compare_wordHitsByQueryPos(const WordHitPtr word_hit1, const WordHitPtr word_hit2);
bool is_collinear(const std::list<WordHitPtr>& wordList_);
