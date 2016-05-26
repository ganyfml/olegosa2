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
	if(!indexCreate((*voidPtr2TPtr(impl_)), seqan::EsaSA())) 
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

char SeqSuffixArray::char_at(int index) const
{
	return rawtextAt(index, *voidPtr2TPtr(impl_));
}

long SeqSuffixArray::seq_length() const
{
	return length(*voidPtr2TPtr(impl_));
}

void SeqSuffixArray::saveSA(const std::string& index_file_name) const
{
	if(!save(*voidPtr2TPtr(impl_), toCString(index_file_name)))
	{
		THROW_RUNTIME_ERROR_MSG("Index Saved Failed for " + index_file_name);
	}
}

unsigned long SeqSuffixArray::SAIndex2SeqPos(unsigned long SAIndex) const
{
	return saAt(SAIndex, *voidPtr2TPtr(impl_));
}

SeqString SeqSuffixArray::getSeq_bySAIndex(unsigned long SAIndex, int seq_length) const
{
	SeqString seq;
	seq.set_pointer(new SeqanString(infixWithLength(indexText(*voidPtr2TPtr(impl_)), saAt(SAIndex, *voidPtr2TPtr(impl_)), seq_length)));
	return seq;
}
