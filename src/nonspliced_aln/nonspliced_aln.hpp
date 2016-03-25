// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/seqString.hpp>
#include <seqan_api/SeqSuffixArray.hpp>

struct aln_nonspliceOpt
{
	int score_mismatch = 1;
	int score_gapOpen = 1;
	int score_gapExtension = 1;

	int max_gapOpen = 2;
	int max_gapExt = 6;
	int max_mismatch = 5;
	int max_diff = 10;

	bool allow_mismatch = true;
};

void aln_nonsplice(const SeqSuffixArray& reference, const SeqString& query, const aln_nonspliceOpt& opt);
