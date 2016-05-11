// vim: set noexpandtab tabstop=2:

#include <queue>
#include <nonspliced_aln/genmu.hpp>
#include <nonspliced_aln/MutationEntry.hpp>
#include <seqan_api/SeqanAPIUtil.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

void produceInsertion(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt)
{
	if(origin.state == MutationEntry::State::STATE_D) return;

	if((origin.state == MutationEntry::State::STATE_I && origin.gap_mm.num_gapExt() >= opt.max_gapExt)
			|| (origin.state == MutationEntry::State::STATE_M && origin.gap_mm.num_gapOpen() >= opt.max_gapOpen))
		return;

	SeqanSAIter ref_iter = origin.ref_iter;	
	for(char char_to_insert : {'A', 'T', 'C', 'G'})
	{
		MutationEntry entry_with_insert(origin);
		if(origin.state == MutationEntry::State::STATE_M)
		{
			entry_with_insert.state = MutationEntry::State::STATE_I;
			++entry_with_insert.gap_mm.num_gapOpenRef;
		}
		else
		{
			++entry_with_insert.gap_mm.num_gapExtRef;
		}

		unsigned long ref_iter_seq_length = length(representative(ref_iter));
		if(origin.extra_step == 0)
		{
			if(seqan::goDown(ref_iter, char_to_insert))
			{
				entry_with_insert.extra_step = length(representative(ref_iter)) - ref_iter_seq_length - 1;
				entry_with_insert.ref_iter = ref_iter;
				mutation_queue.emplace(entry_with_insert);
				seqan::goUp(ref_iter);
			}
		}
		else
		{
			if(representative(origin.ref_iter)[ref_iter_seq_length - origin.extra_step] == char_to_insert)
			{
				entry_with_insert.ref_iter = ref_iter;
				--entry_with_insert.extra_step;
				mutation_queue.emplace(entry_with_insert);
			}
		}
	}
}

void produceDeletion(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt)
{
	if(origin.state == MutationEntry::State::STATE_I) return;
	if((origin.state == MutationEntry::State::STATE_D && origin.gap_mm.num_gapExt() >= opt.max_gapExt)
			|| (origin.state == MutationEntry::State::STATE_M && origin.gap_mm.num_gapOpen() >= opt.max_gapOpen)
		)
		return;

	MutationEntry entry_with_del(origin);
	++entry_with_del.query_pos;
	if(origin.state == MutationEntry::State::STATE_M)
	{
		entry_with_del.state = MutationEntry::State::STATE_D;
		++entry_with_del.gap_mm.num_gapOpenQuery;
	}
	else
	{
		++entry_with_del.gap_mm.num_gapExtQuery;
	}
	mutation_queue.emplace(entry_with_del);
}

void produceMismatch(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt, char next_char)
{
	if(origin.gap_mm.num_mismatch >= opt.max_mismatch) return;

	SeqanSAIter ref_iter = origin.ref_iter;	

	unsigned long ref_iter_seq_length = length(representative(ref_iter));
	for(char char_to_insert : {'A', 'T', 'C', 'G'})
	{
		if(char_to_insert != next_char)
		{
			MutationEntry entry_with_insert(origin);
			entry_with_insert.state = MutationEntry::State::STATE_M;
			++entry_with_insert.gap_mm.num_mismatch;
			++entry_with_insert.query_pos;

			if(origin.extra_step == 0)
			{
				if(seqan::goDown(ref_iter, char_to_insert))
				{
					entry_with_insert.ref_iter = ref_iter;
					entry_with_insert.extra_step = length(representative(ref_iter)) - ref_iter_seq_length - 1;
					mutation_queue.emplace(entry_with_insert);
					seqan::goUp(ref_iter);
				}
			}
			else
			{
				if(representative(ref_iter)[ref_iter_seq_length - origin.extra_step] == char_to_insert)
				{
					entry_with_insert.ref_iter = ref_iter;
					--entry_with_insert.extra_step;
					mutation_queue.emplace(entry_with_insert);
				}
			}
		}
	}
}

void produceMatch(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, char next_char)
{
	MutationEntry new_entry;
	if(origin.produceMatchEntry(new_entry, next_char))
		mutation_queue.emplace(new_entry);
}
