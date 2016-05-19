// vim: set noexpandtab tabstop=2:

#pragma once

#include <string>
#include <memory>
#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqSuffixArray.hpp>

class SeqFinder
{
	public:
		SeqFinder(const SeqSuffixArray& seq_SA);
		bool find(const SeqString& seq);
		unsigned long position() const;
		void clear();
	private:
		void* impl_;
};
