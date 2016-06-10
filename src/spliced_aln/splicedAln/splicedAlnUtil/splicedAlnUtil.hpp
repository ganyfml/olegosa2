// vim: set noexpandtab tabstop=2:

#pragma once

#include <seqan_api/SeqString.hpp>
#include <spliced_aln/Word.hpp>
#include <spliced_aln/WordHit.hpp>
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <spliced_aln/WordHitsGroup.hpp>
#include <list>
#include <vector>

void generate_words(const SeqString& query, std::vector<WordPtr>& words, const AlnSpliceOpt& opt);

void collect_wordHits(const std::vector<WordPtr>& words, std::list<WordHitPtr>& wordHitList, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt);

void group_wordHits_wordHitsGroup(const std::list<WordHitPtr>& hits, std::list<WordHitsGroupPtr>& groups, int max_intron_size);
