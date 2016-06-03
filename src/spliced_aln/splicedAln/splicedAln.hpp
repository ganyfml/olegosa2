// vim: set noexpandtab tabstop=2:

#pragma once

#include <queue>
#include <util/AlnResult.hpp>
#include <seqan_api/SeqSuffixArray.hpp>
#include <seqan_api/SeqString.hpp>
#include <spliced_aln/AlnSpliceOpt.hpp>

void splicedAln(const SeqString& query, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt);
