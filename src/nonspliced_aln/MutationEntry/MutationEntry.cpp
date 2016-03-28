// vim: set noexpandtab tabstop=2:

#include <MutationEntry.hpp>
using namespace seqan;

void MutationEntry::produceInsertion(std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt)
{
	if(state == State::STATE_D)
		return;
	if((state == State::STATE_I && gap_mm.num_gapExt() >= opt.max_gapExt)
			|| (state == State::STATE_M && gap_mm.num_gapOpen() >= opt.max_gapOpen))
		return;

	for(char char_to_insert : {'A', 'T', 'C', 'G'})
	{
		if(seqan::goDown(ref_iter, char_to_insert))
		{
			MutationEntry entry_with_insert(*this);
			if(state == State::STATE_M)
			{
				entry_with_insert.state = State::STATE_I;
				++entry_with_insert.gap_mm.num_gapOpenRef;
			}
			else
			{
				++entry_with_insert.gap_mm.num_gapExtRef;
			}
			mutation_queue.emplace(entry_with_insert);
			seqan::goUp(ref_iter);
		}
	}
}

void MutationEntry::produceDeletion(std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt)
{
	if(state == State::STATE_I)
		return;
	if((state == State::STATE_D && gap_mm.num_gapExt() >= opt.max_gapExt)
			|| (state == State::STATE_M && gap_mm.num_gapOpen() >= opt.max_gapOpen)
	  )
		return;

	MutationEntry entry_with_insert(*this);
	++entry_with_insert.ref_pos;
	if(state == State::STATE_M)
	{
		entry_with_insert.state = State::STATE_D;
		++entry_with_insert.gap_mm.num_gapOpenQuery;
	}
	else
	{
		++entry_with_insert.gap_mm.num_gapExtQuery;
	}
	mutation_queue.emplace(entry_with_insert);
}

void MutationEntry::produceMismatch(std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt, char next_char)
{
	if(gap_mm.num_mismatch >= opt.max_mismatch)
		return;

	for(char char_to_insert : {'A', 'T', 'C', 'G'})
	{
		if(char_to_insert != next_char && seqan::goDown(ref_iter, char_to_insert))
		{
			MutationEntry entry_with_insert(*this);
			entry_with_insert.state = State::STATE_M;
			++entry_with_insert.gap_mm.num_mismatch;
			++entry_with_insert.ref_pos;
			mutation_queue.emplace(entry_with_insert);
			seqan::goUp(ref_iter);
		}
	}
}

void MutationEntry::produceMatch(std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt, char next_char)
{
	if(seqan::goDown(ref_iter, next_char))
	{
		MutationEntry entry_with_insert(*this);
		entry_with_insert.state = State::STATE_M;
		++entry_with_insert.ref_pos;
		mutation_queue.emplace(entry_with_insert);
		seqan::goUp(ref_iter);
	}
}
