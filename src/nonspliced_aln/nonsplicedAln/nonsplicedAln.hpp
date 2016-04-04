// vim: set noexpandtab tabstop=2:

#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqSuffixArray.hpp>
#include <nonspliced_aln/alnNonspliceOpt.hpp>

void nonsplicedAln(const SeqString& query, const SeqSuffixArray& ref_SAIndex, const alnNonspliceOpt& opt);
