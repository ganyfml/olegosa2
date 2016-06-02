// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/SeqSuffixArray.hpp>
#include <seqan_api/SeqString.hpp>

double cal_seqs_score(long fragment_size, const SeqString& ref_seq, double (&global_score_matrix)[4][60], double* global_score_background);

double cal_splice_score(const SeqSuffixArray& ref_IndexSA, long splice_begin, long splice_end);
