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
		~SeqString();
		unsigned long get_length();
		SeqSegmentSuffix get_suffix(unsigned long pos);
		SeqSegmentInfix get_infix(unsigned long pos_begin, unsigned long pos_end);
		SeqSegmentPrefix get_prefix(unsigned long pos);
		const void* get_pointer() const {return seqan_seqString_;}
		void erase_back();
	private:
		void* seqan_seqString_;
};

std::ostream& operator<<(std::ostream& os, const SeqString& obj);
