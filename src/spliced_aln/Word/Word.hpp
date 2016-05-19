// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/SeqString.hpp>
#include <list>
#include <iostream>

struct Word
{
	int id;
	int num_hits;
	int length;
	int strand;
	long query_pos;
	long ref_pos;
	SeqString seq;

	Word(int word_id)
		: id(word_id), num_hits(0), length(0)
			, strand(0), query_pos(0), ref_pos(0) {}

	void display()
	{
		std::cout << "Word ID: " << id << " with " << num_hits << " hits" << std::endl;
		std::cout << "query_pos: " << query_pos << ", ref_pos: " << ref_pos << std::endl;
	}
};

typedef std::shared_ptr<Word> WordPtr;

bool compare_wordsByHitDiagonal(const WordPtr word1, const WordPtr word2);
bool compare_wordsByRefPos(const WordPtr word1, const WordPtr word2);
bool compare_wordsByQueryPos(const WordPtr word1, const WordPtr word2);
bool compare_wordsByRefAndStrand(const WordPtr word1, const WordPtr word2);
bool check_wordListsColinearity(const std::list<WordPtr>& wordList_);
