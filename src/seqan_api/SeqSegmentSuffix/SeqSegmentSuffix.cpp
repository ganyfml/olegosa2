// vim: set noexpandtab tabstop=2:

#include <seqan/sequence.h>
#include <seqan/seq_io.h>
#include "SeqSegmentSuffix.hpp"

typedef seqan::Segment<seqan::String<seqan::SimpleType<unsigned char, seqan::Dna5_>, seqan::Alloc<void> >, seqan::SuffixSegment> T;

typedef seqan::Dna5String seqanString;

SeqSegmentSuffix::SeqSegmentSuffix(const void * other)
	: impl_ (
			const_cast<T*>(
				static_cast<const T*>(other)
				)
			)
{}

SeqSegmentSuffix::~SeqSegmentSuffix()
{
	delete static_cast<T*>(impl_);
}

std::ostream& operator<<(std::ostream& os, const SeqSegmentSuffix& obj)
{
	seqanString to_display = *const_cast<T*>(
			static_cast<const T*>(
				obj.get_pointer()
				)
			);
	return os << to_display;
}
