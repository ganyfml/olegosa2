// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqIndex.hpp>
#include <seqan_api/SeqFinder.hpp>

class Ref
{
	public:
		Ref(const std::string& index_file);
		Ref(const SeqIndex& index);
		bool contains(const SeqString& query);
		bool find(const SeqString& query) { return search_finder_->find(query); }
		unsigned long position() const { return search_finder_->position(); }
		void reset_finder() { search_finder_->clear(); }

	private:
		SeqFinderPtr search_finder_;
};
