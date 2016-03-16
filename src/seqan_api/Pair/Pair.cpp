// vim: set noexpandtab tabstop=2:

#include <seqan_api/Pair.hpp>
#include <seqan/basic.h>

typedef seqan::Pair<unsigned> T;

inline T* voidPtr2TPtr(void* original_ptr)
{
	return static_cast<T*>(original_ptr);
}

Pair::Pair(unsigned first, unsigned second)
	: impl_(new T(first, second))
{}

Pair::~Pair()
{
	delete voidPtr2TPtr(impl_);
}

unsigned Pair::first() const
{
	return voidPtr2TPtr(impl_)->i1;
}

unsigned Pair::second() const
{
	return voidPtr2TPtr(impl_)->i2;
}
