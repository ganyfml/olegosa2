// vim: set noexpandtab tabstop=2:

#include <list>
#include <nonspliced_aln/genmu.hpp>
#include <nonspliced_aln/StateEntry.hpp>
#include <seqan_api/SeqanAPIUtil.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

void add_to_processing_list(const StateEntry& to_add, std::list<StateEntry>& se_list)
{
	if(to_add.gap_mm.sum())
	{
		for(auto iter = se_list.begin(); iter != se_list.end(); ++iter)
		{
			if(to_add.ref_iter.get_SArange() == (*iter).ref_iter.get_SArange())
			{
				return;
			}
		}
	}
	se_list.push_front(to_add);
}


void produceInsertionFromI(const StateEntry& origin, std::list<StateEntry>& se_list, const alnNonspliceOpt& opt)
{
	for(char insert_char: {'A', 'T', 'C', 'G'})
	{
		if(origin.gap_mm.num_gapExt() < opt.max_gapExt)
		{
			StateEntry se = origin;
			++se.gap_mm.num_gapExtRef;
			if(se.appendChar(insert_char))
			{
				add_to_processing_list(se, se_list);
			}
		}
	}
}

void produceInsertionFromM(const StateEntry& origin, std::list<StateEntry>& se_list, const alnNonspliceOpt& opt)
{
	for(char insert_char: {'A', 'T', 'C', 'G'})
	{
		if(origin.gap_mm.num_gapOpen() < opt.max_gapOpen)
		{
			StateEntry se = origin;
			se.state = StateEntry::State::STATE_I;
			++se.gap_mm.num_gapOpenRef;
			if(se.appendChar(insert_char))
			{
				add_to_processing_list(se, se_list);
			}
		}
	}
}

void produceDeletionFromD(const StateEntry& origin, std::list<StateEntry>& se_list, const alnNonspliceOpt& opt)
{
	if(origin.gap_mm.num_gapExt() < opt.max_gapExt)
	{
		StateEntry se = origin;
		++se.query_pos;
		++se.gap_mm.num_gapExtQuery;
		add_to_processing_list(se, se_list);
	}
}

void produceDeletionFromM(const StateEntry& origin, std::list<StateEntry>& se_list, const alnNonspliceOpt& opt)
{
	if(origin.gap_mm.num_gapOpen() < opt.max_gapOpen)
	{
		StateEntry se = origin;
		se.state = StateEntry::State::STATE_D;
		++se.query_pos;
		++se.gap_mm.num_gapOpenQuery;
		add_to_processing_list(se, se_list);
	}
}

void produceMatchAndMismatch(const StateEntry& origin, std::list<StateEntry>& se_list, const alnNonspliceOpt& opt, char next_char)
{
	for(char insert_char: {'A', 'T', 'C', 'G'})
	{
		StateEntry se;
		if(insert_char!= next_char)
		{
			if(origin.gap_mm.num_mismatch < opt.max_mismatch)
			{
				origin.produceMismatchEntry(se);
				if(se.appendChar(insert_char))
				{
					add_to_processing_list(se, se_list);
				}
			}
		}
		else
		{
			origin.produceMatchEntry(se);
			if(se.appendChar(insert_char))
			{
				add_to_processing_list(se, se_list);
			}
		}
	}
}
