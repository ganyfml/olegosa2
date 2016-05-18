// vim: set noexpandtab tabstop=2:

#pragma once

#include <nonspliced_aln/StateEntry.hpp>

void produceInsertion(const StateEntry& origin, std::queue<StateEntry>& mutation_queue, const alnNonspliceOpt& opt);
void produceDeletion(const StateEntry& origin, std::queue<StateEntry>& mutation_queue, const alnNonspliceOpt& opt);
void produceMismatch(const StateEntry& origin, std::queue<StateEntry>& mutation_queue, const alnNonspliceOpt& opt, char next_char);
void produceMatch(const StateEntry& origin, std::queue<StateEntry>& mutation_queue, char next_char);
