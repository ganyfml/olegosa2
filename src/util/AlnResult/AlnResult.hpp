// vim: set noexpandtab tabstop=2:

#pragma once;

#include <seqan_api/SeqString.hpp>

struct AlnResult
{
	SeqString seq;
	unsigned long ref_pos;
	long num_hits;
};
