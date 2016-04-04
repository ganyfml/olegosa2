// vim: set noexpandtab tabstop=2:

#include <MutationEntry.hpp>

using namespace seqan;

void MutationEntry::produceInsertion(std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt)
{
	if(state == State::STATE_D) return;

	if((state == State::STATE_I && gap_mm.num_gapExt() >= opt.max_gapExt)
			|| (state == State::STATE_M && gap_mm.num_gapOpen() >= opt.max_gapOpen))
		return;

	for(char char_to_insert : {'A', 'T', 'C', 'G'})
	{
		unsigned long ref_iter_seq_length = length(representative(ref_iter));
		if(pos_offset == 0)
		{
			if(seqan::goDown(ref_iter, char_to_insert))
			{
				MutationEntry entry_with_insert(*this);
				entry_with_insert.pos_offset = length(representative(ref_iter)) - ref_iter_seq_length - 1;
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
		else
		{
			if(representative(ref_iter)[ref_iter_seq_length - pos_offset] == char_to_insert)
			{
				MutationEntry entry_with_insert(*this);
				--entry_with_insert.pos_offset;
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
			}
		}
	}
}

void MutationEntry::produceDeletion(std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt)
{
	if(state == State::STATE_I) return;
	if((state == State::STATE_D && gap_mm.num_gapExt() >= opt.max_gapExt)
			|| (state == State::STATE_M && gap_mm.num_gapOpen() >= opt.max_gapOpen)
		)
		return;

	MutationEntry entry_with_del(*this);
	++entry_with_del.ref_pos;
	if(state == State::STATE_M)
	{
		entry_with_del.state = State::STATE_D;
		++entry_with_del.gap_mm.num_gapOpenQuery;
	}
	else
	{
		++entry_with_del.gap_mm.num_gapExtQuery;
	}
	mutation_queue.emplace(entry_with_del);
}

void MutationEntry::produceMismatch(std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt, char next_char)
{
	if(gap_mm.num_mismatch >= opt.max_mismatch) return;

	for(char char_to_insert : {'A', 'T', 'C', 'G'})
	{
		unsigned long ref_iter_seq_length = length(representative(ref_iter));
		if(char_to_insert != next_char)
		{
			if(pos_offset == 0)
			{
				if(seqan::goDown(ref_iter, char_to_insert))
				{
					MutationEntry entry_with_insert(*this);
					entry_with_insert.pos_offset = length(representative(ref_iter)) - ref_iter_seq_length - 1;
					entry_with_insert.state = State::STATE_M;
					++entry_with_insert.gap_mm.num_mismatch;
					++entry_with_insert.ref_pos;
					mutation_queue.emplace(entry_with_insert);
					seqan::goUp(ref_iter);
				}
			}
			else
			{
				if(representative(ref_iter)[ref_iter_seq_length - pos_offset] == char_to_insert)
				{
					MutationEntry entry_with_insert(*this);
					--entry_with_insert.pos_offset;
					entry_with_insert.state = State::STATE_M;
					++entry_with_insert.gap_mm.num_mismatch;
					++entry_with_insert.ref_pos;
					mutation_queue.emplace(entry_with_insert);
				}
			}
		}
	}
}

void MutationEntry::produceMatch(std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt, char next_char)
{
	unsigned long ref_iter_seq_length = length(representative(ref_iter));
	if(pos_offset == 0)
	{
		if(seqan::goDown(ref_iter, next_char))
		{
			MutationEntry entry_with_insert(*this);
			entry_with_insert.pos_offset = length(representative(ref_iter)) - ref_iter_seq_length - 1;
			entry_with_insert.state = State::STATE_M;
			++entry_with_insert.ref_pos;
			mutation_queue.emplace(entry_with_insert);
			seqan::goUp(ref_iter);
		}
	}
	else
	{
		if(representative(ref_iter)[ref_iter_seq_length - pos_offset] == next_char)
		{
			MutationEntry entry_with_insert(*this);
			--entry_with_insert.pos_offset;
			entry_with_insert.state = State::STATE_M;
			++entry_with_insert.ref_pos;
			mutation_queue.emplace(entry_with_insert);	
		}
	}
}
