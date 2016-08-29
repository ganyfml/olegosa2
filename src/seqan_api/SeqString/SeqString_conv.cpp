// vim: set noexpandtab tabstop=2:

#include <seqan_api/SeqString_conv.hpp>

seqan::Dna5String* conv_back(const SeqString& origin)
{
	return static_cast<seqan::Dna5String*>(const_cast<void*>(origin.get_pointer()));
}
