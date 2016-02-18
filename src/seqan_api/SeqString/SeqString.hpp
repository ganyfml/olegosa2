// vim: set noexpandtab tabstop=2:

#pragma once

#include <string>
#include <seqan_api/SeqanAPIUtil.hpp>
#include <seqan_api/SeqSegmentInfix.hpp>
#include <seqan_api/SeqSegmentPrefix.hpp>
#include <seqan_api/SeqSegmentSuffix.hpp>

class SeqString
{
	public:
		SeqString(const std::string& seq);
		SeqString(const void*);
		SeqString(const SeqString& that);
		~SeqString();
		unsigned long get_length() const;
		SeqSegmentSuffix get_suffix(unsigned long pos) const;
		SeqSegmentInfix get_infix(unsigned long pos_begin, unsigned long pos_end) const;
		SeqSegmentPrefix get_prefix(unsigned long pos) const;
		const void* get_pointer() const { return impl_; }
		void erase_back();
	private:
		void* impl_;
};

std::ostream& operator<<(std::ostream& os, const SeqString& obj);
