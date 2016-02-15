// vim: set noexpandtab tabstop=2:
#include "SeqString.hpp"
#include <seqan/seq_io.h>
#include <iostream>

typedef seqan::Segment<seqan::String<seqan::SimpleType<unsigned char, seqan::Dna5_>, seqan::Alloc<void>>, seqan::SuffixSegment> SuffixSegment;
typedef seqan::Segment<seqan::String<seqan::SimpleType<unsigned char, seqan::Dna5_>, seqan::Alloc<void>>, seqan::InfixSegment> InfixSegment;
typedef seqan::Segment<seqan::String<seqan::SimpleType<unsigned char, seqan::Dna5_>, seqan::Alloc<void>>, seqan::PrefixSegment> PrefixSegment;
typedef seqan::Dna5String SeqanString;

SeqString::SeqString(const std::string& seq)
	: seqan_seqString_ (static_cast<void*>(new SeqanString(seq)))
{}

SeqString::SeqString(const void* other)
	: seqan_seqString_ (static_cast<void*>(const_cast<SeqanString*>(static_cast<const SeqanString*>(other))))
{}

SeqString::~SeqString()
{
	delete static_cast<SeqanString*>(seqan_seqString_);
}

unsigned long SeqString::get_length()
{
	return seqan::length(*static_cast<SeqanString*>(seqan_seqString_));
}

SeqSegmentSuffix SeqString::get_suffix(unsigned long pos)
{
	SuffixSegment* seg = new SuffixSegment(seqan::suffix(*static_cast<SeqanString*>(seqan_seqString_), pos));
	SeqSegmentSuffix ret (seg);
	return ret;
}

SeqSegmentInfix SeqString::get_infix(unsigned long pos_begin, unsigned long pos_end)
{
	InfixSegment* seg = new InfixSegment(seqan::infix(*static_cast<SeqanString*>(seqan_seqString_), pos_begin, pos_end));
	SeqSegmentInfix ret (seg);
	return ret;
}

SeqSegmentPrefix SeqString::get_prefix(unsigned long pos)
{
	PrefixSegment* seg = new PrefixSegment(seqan::prefix(*static_cast<SeqanString*>(seqan_seqString_), pos));
	SeqSegmentPrefix ret (seg);
	return ret;
}

std::ostream& operator<<(std::ostream& os, const SeqString& obj)
{
	return os << *const_cast<SeqanString*>(static_cast<const SeqanString*>(obj.get_pointer()));
}

void SeqString::erase_back()
{
	seqan::eraseBack(*static_cast<SeqanString*>(seqan_seqString_));
}
