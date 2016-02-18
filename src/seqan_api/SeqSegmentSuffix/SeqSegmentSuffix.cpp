// vim: set noexpandtab tabstop=2:

#include <seqan/sequence.h>
#include <seqan/seq_io.h>
#include "seqan_api/SeqSegmentSuffix.hpp"
#include "seqan_api/SeqString.hpp"

typedef seqan::Segment<seqan::String<seqan::SimpleType<unsigned char, seqan::Dna5_>, seqan::Alloc<void> >, seqan::SuffixSegment> T;

typedef seqan::Dna5String seqanString;

SeqSegmentSuffix::SeqSegmentSuffix(const void * other)
	: impl_ (
			constPointer_convert<T>(other)
			)
{}

SeqSegmentSuffix::~SeqSegmentSuffix()
{
	delete static_cast<T*>(impl_);
}

std::ostream& operator<<(std::ostream& os, const SeqSegmentSuffix& obj)
{
	seqanString to_display = *constPointer_convert<T>(obj.get_pointer());
	return os << to_display;
}
