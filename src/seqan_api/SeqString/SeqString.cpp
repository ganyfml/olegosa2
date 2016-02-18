// vim: set noexpandtab tabstop=2:
#include "seqan_api/SeqString.hpp"
#include <seqan/seq_io.h>
#include <iostream>

typedef seqan::Segment<seqan::String<seqan::SimpleType<unsigned char, seqan::Dna5_>, seqan::Alloc<void>>, seqan::SuffixSegment> SuffixSegment;
typedef seqan::Segment<seqan::String<seqan::SimpleType<unsigned char, seqan::Dna5_>, seqan::Alloc<void>>, seqan::InfixSegment> InfixSegment;
typedef seqan::Segment<seqan::String<seqan::SimpleType<unsigned char, seqan::Dna5_>, seqan::Alloc<void>>, seqan::PrefixSegment> PrefixSegment;
typedef seqan::Dna5String T;

inline T* voidPtr2TPtr(void* original_ptr)
{
	return static_cast<T*>(original_ptr);
}

SeqString::SeqString(const std::string& seq)
	: impl_ (new T(seq))
{}

SeqString::SeqString(const void* other)
	: impl_ (new T(*constVoid2localType<T>(other)))
{}

SeqString::SeqString(const SeqString& copy)
	: impl_ (new T(*constVoid2localType<T>(copy.get_pointer())))
{}

SeqString::~SeqString()
{
	delete voidPtr2TPtr(impl_);
}

unsigned long SeqString::get_length() const
{
	return seqan::length(*voidPtr2TPtr(impl_));
}

SeqSegmentSuffix SeqString::get_suffix(unsigned long pos) const
{
	SuffixSegment* seg = new SuffixSegment(
			seqan::suffix(*voidPtr2TPtr(impl_), pos)
			);
	SeqSegmentSuffix ret (seg);
	return ret;
}

SeqSegmentInfix SeqString::get_infix(unsigned long pos_begin, unsigned long pos_end) const
{
	InfixSegment* seg = new InfixSegment(
			seqan::infix(*voidPtr2TPtr(impl_), pos_begin, pos_end)
			);
	SeqSegmentInfix ret (seg);
	return ret;
}

SeqSegmentPrefix SeqString::get_prefix(unsigned long pos) const
{
	PrefixSegment* seg = new PrefixSegment(
			seqan::prefix(*voidPtr2TPtr(impl_), pos)
			);
	SeqSegmentPrefix ret (seg);
	return ret;
}

void SeqString::erase_back()
{
	seqan::eraseBack(*voidPtr2TPtr(impl_));
}

std::ostream& operator<<(std::ostream& os, const SeqString& obj)
{
	return os << *constVoid2localType<T>(
			obj.get_pointer()
			);
}