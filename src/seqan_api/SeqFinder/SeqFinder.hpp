// vim: set noexpandtab tabstop=2:

#pragma once

#include <string>
#include <SeqString.hpp>

class SeqFinder
{
	public:
		SeqFinder(const SeqIndex& seq_index, const SeqString& seq);
		SeqFinder(const void*);
		~SeqFinder();
	private:
		void* impl_;
		SeqString seq_;
		bool has_next_;
};
