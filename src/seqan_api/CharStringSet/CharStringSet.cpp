// vim: set noexpandtab tabstop=2:
#include <seqan_api/SeqanAPIUtil.hpp>
#include <seqan_api/CharStringSet.hpp>
#include <seqan/seq_io.h>
#include <seqan/modifier.h>
#include <seqan_api/ThrowRuntimeError.hpp>
#include <iostream>

typedef seqan::StringSet<seqan::CharString> T;

inline T* voidPtr2TPtr(void* original_ptr)
{
	return static_cast<T*>(original_ptr);
}

CharStringSet::CharStringSet()
	: impl_(new T()) {}

CharStringSet::CharStringSet(const CharStringSet& that)
	: impl_(new T(*constVoid2localType<T>(that.get_pointer()))) {}

CharStringSet::~CharStringSet()
{
	delete voidPtr2TPtr(impl_);
}

CharStringSet& CharStringSet::operator=(const CharStringSet& other)
{
	impl_ = new T(*constVoid2localType<T>(other.get_pointer()));
	return *this;
}

long CharStringSet::get_length() const
{
	return seqan::length(*voidPtr2TPtr(impl_));
}

CharString CharStringSet::operator[](long idx) const
{
	CharString ret;
	ret.set_pointer(new seqan::CharString((*voidPtr2TPtr(impl_))[idx]));
	return ret;
}
