// vim: set noexpandtab tabstop=2:

#include <seqan_api/SeqSuffixArray.hpp>
#include <seqan_api/SeqString.hpp>
#include <spliced_aln/Word.hpp>
#include <spliced_aln/WordHit.hpp>
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <list>

void generate_words(const SeqString& query, std::list<WordPtr>& wordList, const AlnSpliceOpt& opt);

void collect_wordHits(const std::list<WordPtr>& wordList, std::list<WordHitPtr>& wordHitList, const SeqSuffixArray& ref_SAIndex, const AlnSpliceOpt& opt);
