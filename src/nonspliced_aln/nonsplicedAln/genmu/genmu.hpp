// vim: set noexpandtab tabstop=2:

#pragma once

#include <nonspliced_aln/StateEntry.hpp>


void produceInsertionFromI(const StateEntry& origin, std::queue<StateEntry>& se_queue, const alnNonspliceOpt& opt);

void produceInsertionFromM(const StateEntry& origin, std::queue<StateEntry>& se_queue, const alnNonspliceOpt& opt);

void produceDeletionFromD(const StateEntry& origin, std::queue<StateEntry>& se_queue, const alnNonspliceOpt& opt);

void produceDeletionFromM(const StateEntry& origin, std::queue<StateEntry>& se_queue, const alnNonspliceOpt& opt);

void produceMatchAndMismatch(const StateEntry& origin, std::queue<StateEntry>& se_queue, const alnNonspliceOpt& opt, char next_char);
