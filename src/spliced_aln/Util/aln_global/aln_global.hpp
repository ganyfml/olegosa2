#pragma once

#include <seqan_api/SeqString.hpp>
#include <util/GapAndMM.hpp>

int aln_global(const SeqString& ref_part, const SeqString& query_part, GapAndMM& gap_mm);
void aln_global_cigar(const SeqString& ref, const SeqString& query);
