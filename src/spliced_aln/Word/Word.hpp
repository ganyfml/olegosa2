// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/SeqString.hpp>
#include <list>
#include <iostream>

struct Word
{
	int id;
	int length;
	int query_pos;
	int r_query_pos;
	int num_occ;
	SeqString seq;
	SeqString r_seq;

	Word(int word_id, int query_pos, int r_query_pos, SeqString seq)
		: id(word_id), length(seq.get_length()), query_pos(query_pos), r_query_pos(r_query_pos), num_occ(0), seq(seq), r_seq(seq.get_revcomp()) {}

	void display()
	{
		std::cout << "Word ID: " << id << " with length: " << length << " and " << num_occ <<" hits" << std::endl;
		std::cout << "seq: " << seq << ", query pos: " << query_pos << std::endl;
		std::cout << "reverse seq: " << r_seq << ", reverse query pos: " << r_query_pos << std::endl;
	}
};

typedef std::shared_ptr<Word> WordPtr;
