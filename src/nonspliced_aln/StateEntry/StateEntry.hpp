// vim: set noexpandtab tabstop=2:

#pragma once

#include <iostream>
#include <seqan/index.h>
#include <seqan_api/SeqString.hpp>
#include <util/GapAndMM.hpp>
#include <nonspliced_aln/alnNonspliceOpt.hpp>
#include <nonspliced_aln/SeqSAIter.hpp>

struct StateEntry
{
	enum State
	{
		STATE_M = 0, STATE_I = 1, STATE_D = 2
	};

	typedef seqan::Dna5String SeqanString;
	typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
	typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

	StateEntry(const SeqSAIter& init_iter)
		: query_pos(0), ref_iter(init_iter), state(State::STATE_M), gap_mm(GapAndMM()) {}

	StateEntry()
		: query_pos(0), ref_iter(SeqSAIter()), state(State::STATE_M), gap_mm(GapAndMM()) {}

	StateEntry(const StateEntry& that)
		: query_pos(that.query_pos), ref_iter(that.ref_iter), state(that.state), gap_mm(that.gap_mm) {}

	SeqanString get_seq() const { return ref_iter.get_prefix(); }

	bool appendChar(char x) { return ref_iter.godown_char(x); }

	void display()
	{
		const char* stateName[] = {"STATE_M", "STATE_I", "STATE_D"};
		printf("State Entry state: %s with query_pos %lu\n", stateName[state], query_pos);
		std::cout << "Seq: " << ref_iter.get_prefix() << std::endl;
		gap_mm.display();
	}

	void produceMatchEntry(StateEntry& new_entry) const;
	void produceMismatchEntry(StateEntry& new_entry) const;

	State state;
	SeqSAIter ref_iter;
	unsigned long query_pos;
	GapAndMM gap_mm;
};
