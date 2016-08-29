// vim: set noexpandtab tabstop=2:

#pragma once

#include <util/AlnResult.hpp>
#include <seqan_api/SeqString.hpp>
#include <list>
#include <seqan_api/SeqSuffixArray.hpp>
#include <nonspliced_aln/alnNonspliceOpt.hpp>

void nonsplicedAln(const SeqString& query, std::list<AlnResult>& result_list, const SeqSuffixArray& ref_SAIndex, const alnNonspliceOpt& opt);
