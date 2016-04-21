// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan/index.h>
#include <seqan_api/SeqSuffixArray.hpp>

typedef seqan::Index<seqan::Dna5String, seqan::IndexEsa<>> T;

T* conv_back(const SeqSuffixArray& origin);
