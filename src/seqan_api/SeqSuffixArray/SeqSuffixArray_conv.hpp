// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan/index.h>
#include <seqan_api/SeqSuffixArray.hpp>

seqan::Index<seqan::Dna5String, seqan::IndexEsa<>>* conv_back(const SeqSuffixArray& origin);
