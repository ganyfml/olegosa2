// vim: set noexpandtab tabstop=2:

#include <seqan/sequence.h>
#include <seqan/seq_io.h>
#include "seqan_api/SeqSegmentSuffix.hpp"
#include "seqan_api/SeqString.hpp"

typedef seqan::Segment<seqan::String<seqan::SimpleType<unsigned char, seqan::Dna5_>, seqan::Alloc<void> >, seqan::SuffixSegment> T;

typedef seqan::Dna5String seqanString;

SeqSegmentSuffix::SeqSegmentSuffix(const void* other)
	: impl_(constVoid2localType<T>(other)) {}

SeqSegmentSuffix::~SeqSegmentSuffix()
{
	delete static_cast<T*>(impl_);
}

std::ostream& operator<<(std::ostream& os, const SeqSegmentSuffix& obj)
{
	return os << *constVoid2localType<T>(obj.get_pointer());
}
