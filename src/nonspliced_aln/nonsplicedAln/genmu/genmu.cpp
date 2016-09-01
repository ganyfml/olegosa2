// vim: set noexpandtab tabstop=2:

#include <list>
#include <nonspliced_aln/genmu.hpp>
#include <nonspliced_aln/StateEntry.hpp>
#include <seqan_api/SeqanAPIUtil.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

void produceInsertionFromI(const StateEntry& origin, priority_StateEntry_array& se_array, const alnNonspliceOpt& opt)
{
	for(char insert_char: {'A', 'T', 'C', 'G'})
	{
		if(origin.gap_mm.num_gapExt() < opt.max_gapExt)
		{
			StateEntry se = origin;
			++se.gap_mm.num_gapExtRef;
			if(se.appendChar(insert_char))
			{
				se_array.push(se, opt);
			}
		}
	}
}

void produceInsertionFromM(const StateEntry& origin, priority_StateEntry_array& se_array, const alnNonspliceOpt& opt)
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
				se_array.push(se, opt);
			}
		}
	}
}

void produceDeletionFromD(const StateEntry& origin, priority_StateEntry_array& se_array, const alnNonspliceOpt& opt)
{
	if(origin.gap_mm.num_gapExt() < opt.max_gapExt)
	{
		StateEntry se = origin;
		++se.query_pos;
		++se.gap_mm.num_gapExtQuery;
		se_array.push(se, opt);
	}
}

void produceDeletionFromM(const StateEntry& origin, priority_StateEntry_array& se_array, const alnNonspliceOpt& opt)
{
	if(origin.gap_mm.num_gapOpen() < opt.max_gapOpen)
	{
		StateEntry se = origin;
		se.state = StateEntry::State::STATE_D;
		++se.query_pos;
		++se.gap_mm.num_gapOpenQuery;
		se_array.push(se, opt);
	}
}

void produceMatchAndMismatch(const StateEntry& origin, priority_StateEntry_array& se_array, const alnNonspliceOpt& opt, char next_char, bool allow_mismatch)
{
	for(char insert_char: {'A', 'T', 'C', 'G'})
	{
		if(insert_char != next_char && allow_mismatch)
		{
			if(origin.gap_mm.num_mismatch < opt.max_mismatch)
			{
				StateEntry se = origin;
				if(se.appendChar(insert_char))
				{
					se.state = StateEntry::State::STATE_M;
					++se.query_pos;
					++se.gap_mm.num_mismatch;
					se_array.push(se, opt);
				}
			}
		}
		else if(insert_char == next_char)
		{
			StateEntry se = origin;
			if(se.appendChar(insert_char))
			{
				se.state = StateEntry::State::STATE_M;
				++se.query_pos;
				se_array.push(se, opt);
			}
		}
	}
}
