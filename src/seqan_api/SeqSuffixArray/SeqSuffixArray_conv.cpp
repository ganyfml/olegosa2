// vim: set noexpandtab tabstop=2:

#include <seqan_api/SeqSuffixArray_conv.hpp>

seqan::Index<seqan::Dna5String, seqan::IndexEsa<>>* conv_back(const SeqSuffixArray& origin)
{
	return static_cast<seqan::Index<seqan::Dna5String, seqan::IndexEsa<>>*>(const_cast<void*>(origin.get_pointer()));
}
