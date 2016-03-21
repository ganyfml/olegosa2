// vim: set noexpandtab tabstop=2:

#include <seqan_api/SARange.hpp>
#include <seqan/basic.h>

typedef seqan::Pair<unsigned> T;

inline T* voidPtr2TPtr(void* original_ptr)
{
	return static_cast<T*>(original_ptr);
}

SARange::SARange(unsigned first, unsigned second)
	: impl_(new T(first, second))
{}

SARange::~SARange()
{
	delete voidPtr2TPtr(impl_);
}

unsigned SARange::low() const
{
	return voidPtr2TPtr(impl_)->i1;
}

unsigned SARange::high() const
{
	return voidPtr2TPtr(impl_)->i2;
}
