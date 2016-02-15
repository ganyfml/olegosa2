// vim: set noexpandtab tabstop=2:

#pragma once

#include <SeqString.hpp>
#include <string>

class SeqIndex
{
	public:
		SeqIndex(const SeqString& seq);
		~SeqIndex();
		const void* get_pointer() const {return impl_;}
	private:
		void* impl_;
};

bool indexCreate(SeqIndex& seqIndex);
bool openIndex(SeqIndex& seqIndex, const std::string& fileName);
bool saveIndex(SeqIndex& seqIndex, const std::string& fileName);
