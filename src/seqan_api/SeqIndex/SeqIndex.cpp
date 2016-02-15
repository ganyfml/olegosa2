// vim: set noexpandtab tabstop=2:
#include "SeqIndex.hpp"
#include <seqan/seq_io.h>
#include <seqan/index.h>
#include <iostream>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> T;

SeqIndex::SeqIndex(const SeqString& seq)
{
	impl_ = new T (*const_cast<SeqanString*>(static_cast<const SeqanString*>(seq.get_pointer())));
}

SeqIndex::~SeqIndex()
{
	delete static_cast<T*>(impl_);
}

bool createIndex(SeqIndex& seqIndex)
{
	return seqan::indexCreate(
			*const_cast<T*>(
				static_cast<const T*>(seqIndex.get_pointer())
				)
			, seqan::FibreSA()
			);
}

bool openIndex(SeqIndex& seqIndex, const std::string& fileName)
{
	return seqan::open(
			*const_cast<T*>(
				static_cast<const T*>(seqIndex.get_pointer())
				)
			, seqan::toCString(fileName)
			);
}	

bool saveIndex(SeqIndex& seqIndex, const std::string& fileName)
{
	return seqan::save(
			*const_cast<T*>(
				static_cast<const T*>(seqIndex.get_pointer())
				)
			, seqan::toCString(fileName)
			);
}	
