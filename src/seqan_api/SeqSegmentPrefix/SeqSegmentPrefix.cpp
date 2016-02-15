// vim: set noexpandtab tabstop=2:

#include <seqan/sequence.h>
#include <seqan/seq_io.h>
#include "SeqSegmentPrefix.hpp"

typedef seqan::Segment<seqan::String<seqan::SimpleType<unsigned char, seqan::Dna5_>, seqan::Alloc<void> >, seqan::PrefixSegment> T;

typedef seqan::Dna5String seqanString;

SeqSegmentPrefix::SeqSegmentPrefix(const void * other)
	: impl_ (
			const_cast<T*>(
				static_cast<const T*>(other)
				)
			)
{}

SeqSegmentPrefix::~SeqSegmentPrefix()
{
	delete static_cast<T*>(impl_);
}

std::ostream& operator<<(std::ostream& os, const SeqSegmentPrefix& obj)
{
	seqanString to_display = *const_cast<T*>(
			static_cast<const T*>(
				obj.get_pointer()
				)
			);
	return os << to_display;
}
