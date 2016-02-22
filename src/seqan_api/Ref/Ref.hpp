// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqIndex.hpp>
#include <seqan_api/SeqFinder.hpp>

class Ref
{
	public:
		Ref(const SeqStringPtr ref) : ref_(ref)
	{}
		bool load_SAFinder(const std::string& index_file);
		bool contains(const SeqString& query);
		bool find(const SeqString& query);
		unsigned long location();
		void reset_finder();
		//char operator[](unsigned long idx) const { return rawtextAt(idx, *search_index_); }

	private:
		SeqStringPtr ref_;
		SeqFinderPtr search_finder_;
};
