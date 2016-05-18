// vim: set noexpandtab tabstop=2:

#include <nonspliced_aln/StateEntry.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;

bool StateEntry::produceMatchEntry(StateEntry& new_entry, char match_char) const
{
	new_entry = *this;
	++new_entry.query_pos;
	new_entry.state = StateEntry::State::STATE_M;
	if(new_entry.ref_iter.godown_char(match_char))
	{
		return true;
	}
	else return false;
}

bool StateEntry::produceMismatchEntry(StateEntry& new_entry, const alnNonspliceOpt& opt, char mismatch_char) const
{
	if(this->gap_mm.num_mismatch >= opt.max_mismatch) return false;

	new_entry = *this;
	new_entry.state = StateEntry::State::STATE_M;
	++new_entry.gap_mm.num_mismatch;
	++new_entry.query_pos;
	if(new_entry.ref_iter.godown_char(mismatch_char))
	{
		return true;
	}
	else return false;
}

bool StateEntry::produceDeletionEntry(StateEntry& new_entry, const alnNonspliceOpt& opt) const
{
	if(this->state == StateEntry::State::STATE_I) return false;
	if((this->state == StateEntry::State::STATE_D && this->gap_mm.num_gapExt() >= opt.max_gapExt)
			|| (this->state == StateEntry::State::STATE_M && this->gap_mm.num_gapOpen() >= opt.max_gapOpen)
		)
		return false;

	new_entry = *this;
	++new_entry.query_pos;
	if(this->state == StateEntry::State::STATE_M)
	{
		new_entry.state = StateEntry::State::STATE_D;
		++new_entry.gap_mm.num_gapOpenQuery;
	}
	else
	{
		++new_entry.gap_mm.num_gapExtQuery;
	}
	return true;
}

bool StateEntry::produceInsertionEntry(StateEntry& new_entry, const alnNonspliceOpt& opt, char insert_char) const
{
	if(this->state == StateEntry::State::STATE_D) return false;

	if((this->state == StateEntry::State::STATE_I && this->gap_mm.num_gapExt() >= opt.max_gapExt)
			|| (this->state == StateEntry::State::STATE_M && this->gap_mm.num_gapOpen() >= opt.max_gapOpen))
		return false;

	new_entry = *this;
	if(this->state == StateEntry::State::STATE_M)
	{
		new_entry.state = StateEntry::State::STATE_I;
		++new_entry.gap_mm.num_gapOpenRef;
	}
	else
	{
		++new_entry.gap_mm.num_gapExtRef;
	}

	if(new_entry.ref_iter.godown_char(insert_char))
	{
		return true;
	}
	else return false;
}
