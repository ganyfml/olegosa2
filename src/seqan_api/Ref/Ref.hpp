// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqIndex.hpp>
#include <seqan_api/SeqFinder.hpp>

class Ref
{
	public:
		Ref(const SeqStringPtr ref) : ref_(ref) {}
		bool loadIndex(const std::string& index_file);
		void loadIndex(const SeqIndex& index);
		bool contains(const SeqString& query);
		bool find(const SeqString& query) { return search_finder_->find(query); }
		unsigned long location() const { return search_finder_->location(); }
		void reset_finder() { search_finder_->clear(); }
		char operator[](unsigned long idx) const { return (*ref_)[idx]; }

	private:
		SeqStringPtr ref_;
		SeqFinderPtr search_finder_;
};
