// vim: set noexpandtab tabstop=2:
#include <seqan/seq_io.h>
#include <seqan/index.h>
#include <seqan_api/SeqSuffixArray.hpp>
#include <seqan_api/SeqanAPIUtil.hpp>
#include <seqan_api/ThrowRuntimeError.hpp>

using seqan::toCString;

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> T;

inline T* voidPtr2TPtr(void* original_ptr)
{
	return static_cast<T*>(original_ptr);
}

SeqSuffixArray::SeqSuffixArray(const SeqString& seq)
{
	impl_ = new T(*constVoid2localType<SeqanString>(seq.get_pointer()));
	if(!indexCreate(*voidPtr2TPtr(impl_), seqan::FibreSA())) 
	{
		THROW_RUNTIME_ERROR_MSG("Index Create Failed");
	}
}

SeqSuffixArray::SeqSuffixArray(const std::string& index_file_name)
{
	impl_ = new T();
	if(!open(*voidPtr2TPtr(impl_), toCString(index_file_name)))
	{
		THROW_RUNTIME_ERROR_MSG("Index Open Failed for " + index_file_name);
	}
}

SeqSuffixArray::~SeqSuffixArray()
{
	delete static_cast<T*>(impl_);
}

void SeqSuffixArray::saveSA(const std::string& index_file_name) const
{
	if(!save(*voidPtr2TPtr(impl_), toCString(index_file_name)))
	{
		THROW_RUNTIME_ERROR_MSG("Index Saved Failed for " + index_file_name);
	}
}	
