// vim: set noexpandtab tabstop=2:

#include <seqan_api/SeqString_conv.hpp>

seqan::CharString* conv_back(const CharString& origin)
{
	return static_cast<seqan::CharString*>(const_cast<void*>(origin.get_pointer()));
}
