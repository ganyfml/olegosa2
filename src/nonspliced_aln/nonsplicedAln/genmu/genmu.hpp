// vim: set noexpandtab tabstop=2:

#pragma once

#include <nonspliced_aln/MutationEntry.hpp>

void produceInsertion(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt);
void produceDeletion(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt);
void produceMismatch(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt, char next_char);
void produceMatch(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt, char next_char);
