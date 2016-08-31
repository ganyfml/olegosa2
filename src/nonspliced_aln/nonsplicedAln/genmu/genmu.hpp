// vim: set noexpandtab tabstop=2:

#pragma once

#include <nonspliced_aln/StateEntry.hpp>
#include <nonspliced_aln/priority_StateEntry_array.hpp>


void produceInsertionFromI(const StateEntry& origin, priority_StateEntry_array& se_list, const alnNonspliceOpt& opt);

void produceInsertionFromM(const StateEntry& origin, priority_StateEntry_array& se_list, const alnNonspliceOpt& opt);

void produceDeletionFromD(const StateEntry& origin, priority_StateEntry_array& se_list, const alnNonspliceOpt& opt);

void produceDeletionFromM(const StateEntry& origin, priority_StateEntry_array& se_list, const alnNonspliceOpt& opt);

void produceMatchAndMismatch(const StateEntry& origin, priority_StateEntry_array& se_array, const alnNonspliceOpt& opt, char next_char, bool allow_mismatch);
