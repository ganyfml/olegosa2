// vim: set noexpandtab tabstop=2:

#include <seqan/sequence.h>
#include <SeqSegmentSuffix.hpp>

typedef seqan::Segment<seqan::String<seqan::SimpleType<unsigned char, seqan::Dna5_>, seqan::Alloc<void> >, seqan::SuffixSegment> T;

SeqSegmentSuffix::SeqSegmentSuffix(const void * other)
	: impl_ (static_cast<void *>(const_cast<T*>(static_cast<const T*>(other))))
{}

SeqSegmentSuffix::~SeqSegmentSuffix()
{
	delete static_cast<T*>(impl_);
}

void SeqSegmentSuffix::display()
{
	//std::cout << (*static_cast<T*>(impl_)) << std::endl;	
}
