// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqSuffixArray.hpp>
#include <seqan_api/SeqSuffixArray_conv.hpp>
#include <nonspliced_aln/SeqSAIter.hpp>
#include <vector>

struct MutationTrack
{
	long occ = 0;
	int num_mutation_needed = 0;
};

std::vector<MutationTrack> gen_query_mutationTracks(const SeqString& query, const SeqSuffixArray& ref_SAIndex);
