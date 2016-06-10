// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/SeqString.hpp>
#include <spliced_aln/Word.hpp>
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <vector>

void generate_words(const SeqString& query, std::vector<WordPtr>& words, const AlnSpliceOpt& opt);
