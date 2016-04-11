// vim: set noexpandtab tabstop=2:

#include <queue>
#include <nonspliced_aln/nonsplicedAln.hpp>
#include <nonspliced_aln/MutationEntry.hpp>
#include <seqan_api/SeqanAPIUtil.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

void produceInsertion(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt)
{
	if(origin.state == State::STATE_D) return;

	if((origin.state == State::STATE_I && origin.gap_mm.num_gapExt() >= opt.max_gapExt)
			|| (origin.state == State::STATE_M && origin.gap_mm.num_gapOpen() >= opt.max_gapOpen))
		return;

	SeqanSAIter ref_iter = origin.ref_iter;	
	for(char char_to_insert : {'A', 'T', 'C', 'G'})
	{
		unsigned long ref_iter_seq_length = length(representative(ref_iter));
		if(origin.pos_offset == 0)
		{
			if(seqan::goDown(ref_iter, char_to_insert))
			{
				MutationEntry entry_with_insert(origin);
				entry_with_insert.pos_offset = length(representative(ref_iter)) - ref_iter_seq_length - 1;
				if(origin.state == State::STATE_M)
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
			if(representative(origin.ref_iter)[ref_iter_seq_length - origin.pos_offset] == char_to_insert)
			{
				MutationEntry entry_with_insert(origin);
				--entry_with_insert.pos_offset;
				if(origin.state == State::STATE_M)
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

void produceDeletion(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt)
{
	if(origin.state == State::STATE_I) return;
	if((origin.state == State::STATE_D && origin.gap_mm.num_gapExt() >= opt.max_gapExt)
			|| (origin.state == State::STATE_M && origin.gap_mm.num_gapOpen() >= opt.max_gapOpen)
		)
		return;

	MutationEntry entry_with_del(origin);
	++entry_with_del.ref_pos;
	if(origin.state == State::STATE_M)
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

void produceMismatch(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt, char next_char)
{
	if(origin.gap_mm.num_mismatch >= opt.max_mismatch) return;

	SeqanSAIter ref_iter = origin.ref_iter;	
	for(char char_to_insert : {'A', 'T', 'C', 'G'})
	{
		unsigned long ref_iter_seq_length = length(representative(ref_iter));
		if(char_to_insert != next_char)
		{
			if(origin.pos_offset == 0)
			{
				if(seqan::goDown(ref_iter, char_to_insert))
				{
					MutationEntry entry_with_insert(origin);
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
				if(representative(ref_iter)[ref_iter_seq_length - origin.pos_offset] == char_to_insert)
				{
					MutationEntry entry_with_insert(origin);
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

void produceMatch(const MutationEntry& origin, std::queue<MutationEntry>& mutation_queue, const alnNonspliceOpt& opt, char next_char)
{
	SeqanSAIter ref_iter = origin.ref_iter;
	unsigned long ref_iter_seq_length = length(representative(ref_iter));
	if(origin.pos_offset == 0)
	{
		if(seqan::goDown(ref_iter, next_char))
		{
			MutationEntry entry_with_insert(origin);
			entry_with_insert.pos_offset = length(representative(ref_iter)) - ref_iter_seq_length - 1;
			entry_with_insert.state = State::STATE_M;
			++entry_with_insert.ref_pos;
			mutation_queue.emplace(entry_with_insert);
			seqan::goUp(ref_iter);
		}
	}
	else
	{
		if(representative(ref_iter)[ref_iter_seq_length - origin.pos_offset] == next_char)
		{
			MutationEntry entry_with_insert(origin);
			--entry_with_insert.pos_offset;
			entry_with_insert.state = State::STATE_M;
			++entry_with_insert.ref_pos;
			mutation_queue.emplace(entry_with_insert);	
		}
	}
}

void nonsplicedAln(const SeqString& query, const SeqSuffixArray& ref_SAIndex, const alnNonspliceOpt& opt)
{
	//Change query and ref_SAIndex back to seqan type
	SeqanString query_ref = *constVoid2localType<SeqanString>(query.get_pointer());
	SeqanSA sa_ref = *constVoid2localType<SeqanSA>(ref_SAIndex.get_pointer());
	SeqanSAIter init_iter(sa_ref);

	//Init start
	MutationEntry init_mutation_entry(init_iter);
	std::queue<MutationEntry> mutation_queue;
	mutation_queue.emplace(init_mutation_entry);

	while(!mutation_queue.empty())
	{
		MutationEntry entry = mutation_queue.front();
		mutation_queue.pop();
		//If the potential has been found
		if(entry.ref_pos == query.get_length())
		{
			//Debug
			using namespace std;
			auto result = entry.get_seq();
			cout << prefix(result, length(result) - entry.pos_offset) << endl;
			//End
		}
		else
		{
			//deal with inseration, deletion, mismatch, and match
			if(entry.ref_pos != 0)
			{
				produceInsertion(entry, mutation_queue, opt);
			}

			produceDeletion(entry, mutation_queue, opt);

			produceMismatch(entry, mutation_queue, opt, query[entry.ref_pos]);

			produceMatch(entry, mutation_queue, opt, query[entry.ref_pos]);
		}
	}
}
