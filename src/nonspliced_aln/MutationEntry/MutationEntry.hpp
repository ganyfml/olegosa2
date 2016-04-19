// vim: set noexpandtab tabstop=2:

#pragma once

#include <iostream>
#include <seqan/index.h>
#include <seqan_api/SeqString.hpp>
#include <util/GapAndMM.hpp>
#include <nonspliced_aln/alnNonspliceOpt.hpp>

struct MutationEntry
{
	enum State
	{
		STATE_M = 0, STATE_I = 1, STATE_D = 2
	};

	typedef seqan::Dna5String SeqanString;
	typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
	typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

	MutationEntry(const SeqanSAIter& init_iter)
		: query_pos(0), extra_step(0), ref_iter(init_iter), state(State::STATE_M) {}

	MutationEntry(const MutationEntry& that)
		: query_pos(that.query_pos), extra_step(that.extra_step), ref_iter(that.ref_iter), state(that.state), gap_mm(that.gap_mm) {}

	SeqanString get_seq() const { return seqan::representative(ref_iter); }

	void display()
	{
		const char stateName[] = {'M', 'I', 'D'};
		printf("Mutation Entry state: %c with query_pos %lu, extra_step %lu\n", stateName[state], query_pos, extra_step);
		std::cout << "Seq: " << representative(ref_iter) << std::endl;
		gap_mm.display();
	}

	State state;
	SeqanSAIter ref_iter;
	unsigned long query_pos;
	unsigned long extra_step;
	GapAndMM gap_mm;
};
