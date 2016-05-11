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
