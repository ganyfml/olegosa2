// vim: set noexpandtab tabstop=2:
#include <seqan_api/SeqanAPIUtil.hpp>
#include <seqan_api/CharString.hpp>
#include <seqan/seq_io.h>
#include <seqan/modifier.h>
#include <iostream>

typedef seqan::CharString T;

inline T* voidPtr2TPtr(void* original_ptr)
{
	return static_cast<T*>(original_ptr);
}

CharString::CharString()
	: impl_(new T()) {}

CharString::CharString(const CharString& that)
	: impl_(new T(*constVoid2localType<T>(that.get_pointer()))) {}

CharString::CharString(const std::string& id)
	: impl_(new T(id)) {}

CharString::~CharString()
{
	delete voidPtr2TPtr(impl_);
}

CharString& CharString::operator=(const CharString& other)
{
	impl_ = new T(*constVoid2localType<T>(other.get_pointer()));
	return *this;
}

std::ostream& operator<<(std::ostream& os, const CharString& obj)
{
	return os << *constVoid2localType<T>(obj.get_pointer());
}
