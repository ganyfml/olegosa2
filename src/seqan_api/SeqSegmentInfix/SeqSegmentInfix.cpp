// vim: set noexpandtab tabstop=2:

#include <seqan/sequence.h>
#include <SeqSegmentInfix.hpp>

typedef seqan::Segment<seqan::String<seqan::SimpleType<unsigned char, seqan::Dna5_>, seqan::Alloc<void> >, seqan::InfixSegment> T;

SeqSegmentInfix::SeqSegmentInfix(const void * other)
  : impl_ (static_cast<void *>(const_cast<T*>(static_cast<const T*>(other))))
{}

SeqSegmentInfix::~SeqSegmentInfix()
{
  delete static_cast<T*>(impl_);
}
