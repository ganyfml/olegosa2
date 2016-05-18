// vim: set noexpandtab tabstop=2:

#include <queue>
#include <nonspliced_aln/genmu.hpp>
#include <nonspliced_aln/StateEntry.hpp>
#include <seqan_api/SeqanAPIUtil.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

void produceInsertion(const StateEntry& origin, std::queue<StateEntry>& mutation_queue, const alnNonspliceOpt& opt)
{
	for(char char_to_insert : {'A', 'T', 'C', 'G'})
	{
		StateEntry entry_with_insert;
		if(origin.produceInsertionEntry(entry_with_insert, opt, char_to_insert))
		{
			mutation_queue.emplace(entry_with_insert);
		}
	}
}

void produceDeletion(const StateEntry& origin, std::queue<StateEntry>& mutation_queue, const alnNonspliceOpt& opt)
{
	StateEntry entry_with_del;
	if(origin.produceDeletionEntry(entry_with_del, opt))
	{
		mutation_queue.emplace(entry_with_del);
	}
}

void produceMismatch(const StateEntry& origin, std::queue<StateEntry>& mutation_queue, const alnNonspliceOpt& opt, char next_char)
{
	for(char char_to_insert : {'A', 'T', 'C', 'G'})
	{
		if(char_to_insert != next_char)
		{
			StateEntry entry_with_mismatch;
			if(origin.produceMismatchEntry(entry_with_mismatch, opt, char_to_insert))
			{
				mutation_queue.emplace(entry_with_mismatch);
			}
		}
	}
}

void produceMatch(const StateEntry& origin, std::queue<StateEntry>& mutation_queue, char next_char)
{
	StateEntry new_entry;
	if(origin.produceMatchEntry(new_entry, next_char))
	{
		mutation_queue.emplace(new_entry);
	}
}
