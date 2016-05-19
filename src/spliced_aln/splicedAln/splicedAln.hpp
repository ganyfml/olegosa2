// vim: set noexpandtab tabstop=2:

#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqSuffixArray.hpp>
#include <spliced_aln/Word.hpp>
#include <list>

void generate_words(const SeqString& query, std::list<WordPtr>& wordList, const SeqSuffixArray& ref_SAIndex);
