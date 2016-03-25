// vim: set noexpandtab tabstop=2:
#include <seqan/index.h>
#include <seqan/find.h>
#include <iostream>
#include <seqan_api/SeqanAPIUtil.hpp>
#include <seqan_api/SeqFinder.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanIndex;
typedef seqan::Finder<SeqanIndex> T;

inline T* voidPtr2TPtr(void* original_ptr)
{
	return static_cast<T*>(original_ptr);
}

SeqFinder::SeqFinder(const SeqSuffixArray& seq_SA)
: impl_ (
		new T(
			*constVoid2localType<SeqanIndex>(seq_SA.get_pointer())
			)
		) {}

void SeqFinder::clear()
{
	seqan::clear(*voidPtr2TPtr(impl_));
}

bool SeqFinder::find(const SeqString& seq)
{
	return seqan::find(
			*voidPtr2TPtr(impl_)
			, *constVoid2localType<SeqanString>(seq.get_pointer())
			);
}

unsigned long SeqFinder::position() const
{
	return seqan::position(*voidPtr2TPtr(impl_));	
}
