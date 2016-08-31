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

	SeqString get_seq() const { return ref_iter.get_prefix(); }

	bool appendChar(char x) { return ref_iter.godown_char(x); }

	long num_hits() { return ref_iter.num_occ(); }

	long next_hit_pos() { return ref_iter.next_occ_pos(); }

	seqan::Pair<unsigned> get_SArange() {return ref_iter.get_SArange(); }

	int seq_length() { return ref_iter.get_repLength(); }

	void display() const
	{
		const char* stateName[] = {"STATE_M", "STATE_I", "STATE_D"};
		printf("State Entry state: %s with query_pos %lu\n", stateName[state], query_pos);
		std::cout << "Seq: " << ref_iter.get_prefix() << std::endl;
		gap_mm.display();
	}

	int get_score(const alnNonspliceOpt& opt) const
	{
		return gap_mm.num_gapOpen() * opt.score_gapOpen
			+ gap_mm.num_gapExt() * opt.score_gapExt
			+ gap_mm.num_mismatch * opt.score_mismatch;
	}

	void produceMatchEntry(StateEntry& new_entry) const;
	void produceMismatchEntry(StateEntry& new_entry) const;

	long query_pos;
	SeqSAIter ref_iter;
	State state;
	GapAndMM gap_mm;
};
