// vim: set noexpandtab tabstop=2:
#include <seqan/seq_io.h>
#include <seqan/index.h>
#include <iostream>
#include <seqan_api/SeqIndex.hpp>
#include <seqan_api/SeqanAPIUtil.hpp>
#include <throw_runtime_error/throw_runtime_error.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> T;

SeqIndex::SeqIndex(const SeqString& seq)
{
	impl_ = new T(*constVoid2localType<SeqanString>(seq.get_pointer()));
	bool create_successfully = seqan::indexCreate(
			*constVoid2localType<T>(impl_)
			, seqan::FibreSA()
			);

	if(!create_successfully)
	{
		THROW_RUNTIME_ERROR_MSG("Index Create Failed");
	}
}

SeqIndex::SeqIndex(const std::string& index_file_name)
{
	impl_ = new T();
	bool open_successfully = seqan::open(
			*constVoid2localType<T>(impl_)
			, seqan::toCString(index_file_name)
			);

	if(!open_successfully)
	{
		THROW_RUNTIME_ERROR_MSG("Index Open Failed");
	}
}

SeqIndex::~SeqIndex()
{
	delete static_cast<T*>(impl_);
}

void SeqIndex::saveIndex(const std::string& file_name)
{
	bool save_successfully = seqan::save(
			*constVoid2localType<T>(impl_)
			, seqan::toCString(file_name)
			);

	if(!save_successfully)
	{
		THROW_RUNTIME_ERROR_MSG("Index Saved Failed");
	}
}	
