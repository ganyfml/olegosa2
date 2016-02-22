// vim: set noexpandtab tabstop=2:
#include <seqan/index.h>
#include <seqan/find.h>
#include <iostream>
#include <seqan_api/SeqFinder.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanIndex;
typedef seqan::Finder<SeqanIndex> T;

inline SeqanString* voidPtr2TPtr(const void* seq)
{
	return constVoid2localType<SeqanString>(seq);
}

SeqFinder::SeqFinder(const SeqIndex& seq_index)
: impl_ (
		new T(
			*constVoid2localType<SeqanIndex>(seq_index.get_pointer()))
		)
{}

void SeqFinder::clear()
{
	seqan::clear(*static_cast<T*>(impl_));
}

bool SeqFinder::find(const SeqString& seq)
{
	return seqan::find(
			*static_cast<T*>(impl_)
			, *voidPtr2TPtr(seq.get_pointer())
			);
}

unsigned long SeqFinder::location()
{
	return seqan::position(*static_cast<T*>(impl_));	
}
