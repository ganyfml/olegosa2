// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqSuffixArray.hpp>
#include <spliced_aln/Word.hpp>
#include <spliced_aln/wordHit.hpp>
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <vector>
#include <nonspliced_aln/alnNonspliceOpt.hpp>

void generate_words(const SeqString& query, std::vector<WordPtr>& words, const AlnSpliceOpt& opt);

void collect_wordHits(const std::vector<WordPtr>& words, std::list<WordHitPtr>& wordHitList, const SeqSuffixArray& ref_SAIndex, bool revcomp, const alnNonspliceOpt& word_search_opt);
