// vim: set noexpandtab tabstop=2:
#include <seqan_api/SeqanAPIUtil.hpp>
#include <seqan_api/SeqStringSet.hpp>
#include <seqan/seq_io.h>
#include <seqan/basic.h>
#include <seqan_api/ThrowRuntimeError.hpp>
#include <iostream>

typedef seqan::StringSet<seqan::Dna5String> T;

inline T* voidPtr2TPtr(void* original_ptr)
{
	return static_cast<T*>(original_ptr);
}

SeqStringSet::SeqStringSet()
	: impl_(new T()) {}

SeqStringSet::SeqStringSet(const SeqStringSet& that)
	: impl_(new T(*constVoid2localType<T>(that.get_pointer()))) {}

SeqStringSet::~SeqStringSet()
{
	delete voidPtr2TPtr(impl_);
}

SeqStringSet& SeqStringSet::operator=(const SeqStringSet& other)
{
	impl_ = new T(*constVoid2localType<T>(other.get_pointer()));
	return *this;
}

long SeqStringSet::get_length() const
{
	return seqan::length(*voidPtr2TPtr(impl_));
}

SeqString SeqStringSet::operator[](long idx) const
{
	SeqString ret;
	ret.set_pointer(new seqan::Dna5String((*voidPtr2TPtr(impl_))[idx]));
	return ret;
}

void load_seqs(std::string seqFilePath, SeqStringSet& seq, CharStringSet& id)
{
	seqan::SeqFileIn seqFileIn;
	if (!open(seqFileIn, seqan::toCString(seqFilePath)))
	{
		THROW_RUNTIME_ERROR_MSG("ERROR: Could not open the file.\n");
	}

	seqan::StringSet<seqan::CharString>* seqan_id_pointer = new seqan::StringSet<seqan::CharString>();
	seqan::StringSet<seqan::Dna5String>* seqan_seq_pointer = new seqan::StringSet<seqan::Dna5String>();
	try
	{
		readRecords(*seqan_id_pointer, *seqan_seq_pointer, seqFileIn);
	}
	catch (seqan::Exception const & e)
	{
		THROW_RUNTIME_ERROR_MSG("ERROR: Could not read the seq.\n");
	}
	id.set_pointer(seqan_id_pointer);
	seq.set_pointer(seqan_seq_pointer);
}

void load_seqs_with_qual(std::string seqFilePath, SeqStringSet& seq, CharStringSet& id, CharStringSet& qual)
{
	seqan::SeqFileIn seqFileIn;
	if (!open(seqFileIn, seqan::toCString(seqFilePath)))
	{
		THROW_RUNTIME_ERROR_MSG("ERROR: Could not open the file.\n");
	}

	seqan::StringSet<seqan::CharString>* seqan_id_pointer = new seqan::StringSet<seqan::CharString>();
	seqan::StringSet<seqan::Dna5String>* seqan_seq_pointer = new seqan::StringSet<seqan::Dna5String>();
	seqan::StringSet<seqan::CharString>* seqan_qual_pointer = new seqan::StringSet<seqan::CharString>();
	try
	{
		readRecords(*seqan_id_pointer, *seqan_seq_pointer, *seqan_qual_pointer, seqFileIn);
	}
	catch (seqan::Exception const & e)
	{
		THROW_RUNTIME_ERROR_MSG("ERROR: Could not read the seq.\n");
	}
	seq.set_pointer(seqan_seq_pointer);
	id.set_pointer(seqan_id_pointer);
	qual.set_pointer(seqan_qual_pointer);
}
