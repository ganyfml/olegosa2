// vim: set noexpandtab tabstop=2:

#include <nonspliced_aln/MutationEntry.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

bool MutationEntry::produceMatchEntry(MutationEntry& new_entry, char match_char) const
{
	SeqanSAIter origin_iter = this->ref_iter;
	unsigned long ref_iter_seq_length = length(representative(origin_iter));

	new_entry = *this;
	++new_entry.query_pos;
	new_entry.state = MutationEntry::State::STATE_M;

	if(this->extra_step == 0)
	{
		if(seqan::goDown(origin_iter, match_char))
		{
			new_entry.extra_step = length(representative(origin_iter)) - ref_iter_seq_length - 1;
			new_entry.ref_iter = origin_iter;
			return true;
		}
	}
	else
	{
		if(representative(origin_iter)[ref_iter_seq_length - this->extra_step] == match_char)
		{
			--new_entry.extra_step;
			new_entry.state = MutationEntry::State::STATE_M;
			return true;
		}
	}
	return false;
}

bool MutationEntry::produceDeletionEntry(MutationEntry& new_entry, const alnNonspliceOpt& opt) const
{
	if(this->state == MutationEntry::State::STATE_I) return false;
	if((this->state == MutationEntry::State::STATE_D && this->gap_mm.num_gapExt() >= opt.max_gapExt)
			|| (this->state == MutationEntry::State::STATE_M && this->gap_mm.num_gapOpen() >= opt.max_gapOpen)
		)
		return false;

	new_entry = *this;
	++new_entry.query_pos;
	if(this->state == MutationEntry::State::STATE_M)
	{
		new_entry.state = MutationEntry::State::STATE_D;
		++new_entry.gap_mm.num_gapOpenQuery;
	}
	else
	{
		++new_entry.gap_mm.num_gapExtQuery;
	}
	return true;
}

bool MutationEntry::produceMatchEntry(MutationEntry& new_entry, char match_char) const
{
	SeqanSAIter origin_iter = this->ref_iter;
	unsigned long ref_iter_seq_length = length(representative(origin_iter));

	new_entry = *this;
	++new_entry.query_pos;
	new_entry.state = MutationEntry::State::STATE_M;

	if(this->extra_step == 0)
	{
		if(seqan::goDown(origin_iter, match_char))
		{
			new_entry.extra_step = length(representative(origin_iter)) - ref_iter_seq_length - 1;
			new_entry.ref_iter = origin_iter;
			return true;
		}
	}
	else
	{
		if(representative(origin_iter)[ref_iter_seq_length - this->extra_step] == match_char)
		{
			--new_entry.extra_step;
			new_entry.state = MutationEntry::State::STATE_M;
			return true;
		}
	}
	return false;
}
