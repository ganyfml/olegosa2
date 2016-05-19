// vim: set noexpandtab tabstop=2:

#include <seqan_api/SeqSuffixArray_conv.hpp>

T* conv_back(const SeqSuffixArray& origin)
{
	return static_cast<T*>(const_cast<void*>(origin.get_pointer()));
}
