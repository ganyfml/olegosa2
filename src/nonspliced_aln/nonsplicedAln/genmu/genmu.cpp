// vim: set noexpandtab tabstop=2:

#include <queue>
#include <nonspliced_aln/genmu.hpp>
#include <nonspliced_aln/StateEntry.hpp>
#include <seqan_api/SeqanAPIUtil.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

void produceInsertionFromI(const StateEntry& origin, std::queue<StateEntry>& se_queue, const alnNonspliceOpt& opt)
{
	for(char insert_char: {'A', 'T', 'C', 'G'})
	{
		StateEntry se = origin;
		if(origin.gap_mm.num_gapExt() < opt.max_gapExt)
		{
			++se.gap_mm.num_gapExtRef;
			if(se.appendChar(insert_char))
			{
				se_queue.emplace(se);
			}
		}
	}
}

void produceInsertionFromM(const StateEntry& origin, std::queue<StateEntry>& se_queue, const alnNonspliceOpt& opt)
{
	for(char insert_char: {'A', 'T', 'C', 'G'})
	{
		StateEntry se = origin;
		se.state = StateEntry::State::STATE_I;
		if(origin.gap_mm.num_gapOpen() < opt.max_gapOpen)
		{
			++se.gap_mm.num_gapOpenRef;
			if(se.appendChar(insert_char))
			{
				se_queue.emplace(se);
			}
		}
	}
}

void produceDeletionFromD(const StateEntry& origin, std::queue<StateEntry>& se_queue, const alnNonspliceOpt& opt)
{
	if(origin.gap_mm.num_gapExt() < opt.max_gapExt)
	{
		StateEntry se = origin;
		++se.query_pos;
		++se.gap_mm.num_gapExtQuery;
		se_queue.emplace(se);
	}
}

void produceDeletionFromM(const StateEntry& origin, std::queue<StateEntry>& se_queue, const alnNonspliceOpt& opt)
{
	if(origin.gap_mm.num_gapOpen() < opt.max_gapOpen)
	{
		StateEntry se = origin;
		++se.query_pos;
		++se.gap_mm.num_gapOpenQuery;
		se_queue.emplace(se);
	}
}

void produceMatchAndMismatch(const StateEntry& origin, std::queue<StateEntry>& se_queue, const alnNonspliceOpt& opt, char next_char)
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
					se_queue.emplace(se);
				}
			}
		}
		else
		{
			origin.produceMatchEntry(se);
			if(se.appendChar(insert_char))
			{
				se_queue.emplace(se);
			}
		}
	}
}
