// vim: set noexpandtab tabstop=2:
#include <seqan/seq_io.h>
#include <seqan/index.h>
#include <iostream>
#include "SeqIndex.hpp"
#include "SeqFinder.hpp"

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanIndex;
typedef seqan::Finder<SeqanIndex> T;

inline SeqanString* stringPtr(const void* seq)
{
	return const_cast<SeqanString*>(
			static_cast<const SeqanString*>(seq)
			);
}

SeqFinder::SeqFinder(const SeqIndex& seq_index, const SeqString& seq)
	: impl_ (
			new T(
				*const_cast<SeqanIndex*>(
					static_cast<const SeqanIndex*>(seq_index.get_pointer())
					)
				)
			)
			, seq_ (SeqString(seq))
{
	has_next_ = seqan::find(
			*static_cast<T*>(impl_)
			, *stringPtr(seq.get_pointer())
			);
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
			, *stringPtr(seq_.get_pointer())
			);
	return ret;	
}
