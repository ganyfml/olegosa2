// vim: set noexpandtab tabstop=2:
#include <seqan/seq_io.h>
#include <seqan/index.h>
#include <iostream>
#include <seqan_api/SeqIndex.hpp>
#include <seqan_api/SeqanAPIUtil.hpp>
#include <seqan_api/ThrowRuntimeError.hpp>

using seqan::toCString;

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> T;

SeqIndex::SeqIndex(const SeqString& seq)
{
	impl_ = new T(*constVoid2localType<SeqanString>(seq.get_pointer()));
	if(!indexCreate(*constVoid2localType<T>(impl_), seqan::FibreSA())) 
	{
		THROW_RUNTIME_ERROR_MSG("Index Create Failed");
	}
}

SeqIndex::SeqIndex(const std::string& index_file_name)
{
	impl_ = new T();
	if(!open(*constVoid2localType<T>(impl_), toCString(index_file_name)))
	{
		THROW_RUNTIME_ERROR_MSG("Index Open Failed for " + index_file_name);
	}
}

SeqIndex::~SeqIndex()
{
	delete static_cast<T*>(impl_);
}

void SeqIndex::saveIndex(const std::string& file_name)
{
	if(!save(*constVoid2localType<T>(impl_), toCString(file_name)))
	{
		THROW_RUNTIME_ERROR_MSG("Index Saved Failed for " + file_name);
	}
}	
