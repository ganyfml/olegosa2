// vim: set noexpandtab tabstop=2:

#pragma once

#include <string>
#include <seqan_api/SeqString.hpp>

class SeqSuffixArray
{
	public:
		SeqSuffixArray(const SeqString& seq);
		SeqSuffixArray(const std::string& index_file_name);
		~SeqSuffixArray();
		void saveSA(const std::string& index_file_name) const;
		const void* get_pointer() const { return impl_; }
	private:
		void* impl_;
};
