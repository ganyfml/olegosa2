// vim: set noexpandtab tabstop=2:

#pragma once

#include <SeqSegmentInfix.hpp>
#include <SeqSegmentPrefix.hpp>
#include <SeqSegmentSuffix.hpp>
#include <string>

class SeqString
{
	public:
		SeqString(const std::string& seq);
		SeqString(const void*);
		SeqString(const SeqString& copy);
		~SeqString();
		unsigned long get_length() const;
		SeqSegmentSuffix get_suffix(unsigned long pos) const;
		SeqSegmentInfix get_infix(unsigned long pos_begin, unsigned long pos_end) const;
		SeqSegmentPrefix get_prefix(unsigned long pos) const;
		const void* get_pointer() const {return impl_;}
		void erase_back();
	private:
		void* impl_;
};

std::ostream& operator<<(std::ostream& os, const SeqString& obj);
