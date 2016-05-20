// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/SeqString.hpp>
#include <iostream>

struct AlnResult
{
	SeqString seq;
	unsigned long ref_pos;
	long num_hits;

	void display() const
	{
		std::cout << seq << std::endl;
		printf("Ref_pos: %lu, num of hits: %li\n", ref_pos, num_hits);
	}
};
