// vim: set noexpandtab tabstop=2:

#pragma once

#include <memory>
#include <string>

/* FIXME
 * Seems not useful for now
#include "seqan_api/SeqSegmentInfix.hpp"
#include "seqan_api/SeqSegmentPrefix.hpp"
#include "seqan_api/SeqSegmentSuffix.hpp"
 */


class SeqString
{
	public:
		SeqString();
		SeqString(const std::string& seq);
		SeqString(const SeqString& that);
		~SeqString();
		long get_length() const;
		const void* get_pointer() const { return impl_; }
		void set_pointer(void* ptr) { impl_ = ptr; }
		void erase_back();

		SeqString get_infix(int begin_pos, int end_pos) const;
		void make_revcomp();
		SeqString get_revcomp() const;

		SeqString& operator+=(const std::string& rhs);
		SeqString& operator+=(const SeqString& rhs);
		char operator[](long idx) const;

		SeqString& operator=(const SeqString& other);

		friend SeqString operator+(SeqString lhs, const SeqString& rhs);

		/* FIXME
		 * Seems not useful for now
		 SeqSegmentSuffix get_suffix(unsigned long pos) const;
		 SeqSegmentInfix get_infix(unsigned long pos_begin, unsigned long pos_end) const;
		 SeqSegmentPrefix get_prefix(unsigned long pos) const;
		 */

	private:
		void* impl_;
};

std::ostream& operator<<(std::ostream& os, const SeqString& obj);

typedef std::shared_ptr<SeqString> SeqStringPtr;
