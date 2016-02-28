// vim: set noexpandtab tabstop=2:

#pragma once

#include <string>
#include <seqan_api/SeqString.hpp>

class SeqIndex
{
	public:
		SeqIndex(const SeqString& seq);
		SeqIndex(const std::string& index_file_name);
		~SeqIndex();
		bool saveIndex(const std::string& file_name);
		const void* get_pointer() const { return impl_; }
	private:
		void* impl_;
};

