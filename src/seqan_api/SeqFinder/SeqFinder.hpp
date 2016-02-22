// vim: set noexpandtab tabstop=2:

#pragma once

#include <string>
#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqIndex.hpp>

class SeqFinder
{
	public:
		SeqFinder(const SeqIndex& seq_index);
		bool find(const SeqString& seq);
		unsigned long location();
		void clear();
	private:
		void* impl_;
		bool has_next_;
};

typedef std::shared_ptr<SeqFinder> SeqFinderPtr;
