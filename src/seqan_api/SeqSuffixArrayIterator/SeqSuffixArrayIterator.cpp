// vim: set noexpandtab tabstop=2:
#include <seqan/index.h>
#include <seqan_api/SeqanAPIUtil.hpp>
#include <SeqSuffixArrayIterator.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> Dna5SuffixArray;
typedef seqan::Iterator<Dna5SuffixArray, seqan::TopDown<>>::Type T;

inline T* voidPtr2TPtr(void* original_ptr)
{
	return static_cast<T*>(original_ptr);
}

SeqSuffixArrayIterator::SeqSuffixArrayIterator(const SeqSuffixArray& sa)
{
	Dna5SuffixArray* test = constVoid2localType<Dna5SuffixArray>(sa.get_pointer());
	impl_ = new T(*test);
}

SeqSuffixArrayIterator::~SeqSuffixArrayIterator()
{
	delete static_cast<T*>(impl_);
}

bool SeqSuffixArrayIterator::goDown(const SeqString& query)
{
	return seqan::goDown(*voidPtr2TPtr(impl_), *constVoid2localType<SeqanString>(query.get_pointer()));
}
