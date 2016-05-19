// vim: set noexpandtab tabstop=2:

#include <nonspliced_aln/StateEntry.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;

void StateEntry::produceMatchEntry(StateEntry& new_entry) const
{
	new_entry = *this;
	new_entry.state = StateEntry::State::STATE_M;
	++new_entry.query_pos;
}

void StateEntry::produceMismatchEntry(StateEntry& new_entry) const
{
	new_entry = *this;
	new_entry.state = StateEntry::State::STATE_M;
	++new_entry.query_pos;
	++new_entry.gap_mm.num_mismatch;
}
