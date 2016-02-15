// vim: set noexpandtab tabstop=2:

#include <seqan/sequence.h>
#include <SeqSegmentPrefix.hpp>

typedef seqan::Segment<seqan::String<seqan::SimpleType<unsigned char, seqan::Dna5_>, seqan::Alloc<void> >, seqan::PrefixSegment> T;

SeqSegmentPrefix::SeqSegmentPrefix(const void * other)
  : impl_ (static_cast<void *>(const_cast<T*>(static_cast<const T*>(other))))
{}

SeqSegmentPrefix::~SeqSegmentPrefix()
{
  delete static_cast<T*>(impl_);
}
