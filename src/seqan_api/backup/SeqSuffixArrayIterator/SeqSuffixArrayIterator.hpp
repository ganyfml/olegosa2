// vim: set noexpandtab tabstop=2:

#pragma once

#include <string>
#include <seqan_api/SeqSuffixArray.hpp>
#include <seqan_api/SeqString.hpp>

class SeqSuffixArrayIterator
{
	public:
		SeqSuffixArrayIterator(const SeqSuffixArray& sa);
		~SeqSuffixArrayIterator();
		const void* get_pointer() const { return impl_; }
		bool goDown(const SeqString& query);
	private:
		void* impl_;
};
