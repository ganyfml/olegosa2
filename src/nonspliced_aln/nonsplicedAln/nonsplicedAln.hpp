// vim: set noexpandtab tabstop=2:

#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqSuffixArray.hpp>
#include <nonspliced_aln/alnNonspliceOpt.hpp>

void nonsplicedAln(const SeqString& query, const SeqSuffixArray& ref_SAIndex, const alnNonspliceOpt& opt);

//Debug
#include <nonspliced_aln/MutationEntry.hpp>
void produceInsertion(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt);
void produceDeletion(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt);
void produceMismatch(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt, char next_char);
void produceMatch(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt, char next_char);
//End
