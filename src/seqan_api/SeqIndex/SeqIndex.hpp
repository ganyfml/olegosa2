// vim: set noexpandtab tabstop=2:

#pragma once

#include <string>
#include <seqan_api/SeqString.hpp>

class SeqIndex
{
	public:
		SeqIndex(const SeqString& seq);
		~SeqIndex();
		const void* get_pointer() const { return impl_; }
	private:
		void* impl_;
};

bool createIndex(SeqIndex& seqIndex);
bool openIndex(SeqIndex& seqIndex, const std::string& fileName);
bool saveIndex(SeqIndex& seqIndex, const std::string& fileName);
