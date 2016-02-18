// vim: set noexpandtab tabstop=2:
#include <seqan/seq_io.h>
#include <seqan/index.h>
#include <iostream>
#include "seqan_api/SeqFinder.hpp"

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanIndex;
typedef seqan::Finder<SeqanIndex> T;

inline SeqanString* voidPtr2TPtr(const void* seq)
{
	return constVoid2localType<SeqanString> (seq);
}

SeqFinder::SeqFinder(const SeqIndex& seq_index, const SeqString& seq)
	: impl_ (new T(
				*constVoid2localType<SeqanIndex>(seq_index.get_pointer()))
			)
			, seq_ (SeqString(seq))
{
	has_next_ = seqan::find(
			*static_cast<T*>(impl_)
			, *voidPtr2TPtr(seq.get_pointer())
			);
}

SeqFinder::~SeqFinder()
{
	delete static_cast<T*>(impl_);
}

bool SeqFinder::has_next()
{
	return has_next_;
}

unsigned long SeqFinder::next()
{
	unsigned long ret = seqan::position(*static_cast<T*>(impl_)); 
	has_next_ = seqan::find(
			*static_cast<T*>(impl_)
			, *voidPtr2TPtr(seq_.get_pointer())
			);
	return ret;	
}
