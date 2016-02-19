// vim: set noexpandtab tabstop=2:
#include <seqan/seq_io.h>
#include <seqan/index.h>
#include <iostream>
#include <seqan_api/SeqIndex.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> T;

SeqIndex::SeqIndex(const SeqString& seq)
{
	impl_ = new T(*constVoid2localType<SeqanString>(seq.get_pointer()));
}

SeqIndex::~SeqIndex()
{
	delete static_cast<T*>(impl_);
}

bool createIndex(SeqIndex& seq_index)
{
	return seqan::indexCreate(
			*constVoid2localType<T>(seq_index.get_pointer())	
			, seqan::FibreSA()
			);
}

bool openIndex(SeqIndex& seq_index, const std::string& file_name)
{
	return seqan::open(
			*constVoid2localType<T>(seq_index.get_pointer())
			, seqan::toCString(file_name)
			);
}	

bool saveIndex(SeqIndex& seq_index, const std::string& file_name)
{
	return seqan::save(
			*constVoid2localType<T>(seq_index.get_pointer())
			, seqan::toCString(file_name)
			);
}	
