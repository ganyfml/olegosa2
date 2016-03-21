// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqSuffixArray.hpp>
#include <seqan_api/SeqFinder.hpp>

class Ref
{
	public:
		Ref(const SeqIndex& index);
		bool contains(const SeqString& query);
		bool find(const SeqString& query) { return search_finder_.find(query); }
		unsigned long position() const { return search_finder_.position(); }
		void reset_finder() { search_finder_.clear(); }

	private:
		SeqFinder search_finder_;
};
