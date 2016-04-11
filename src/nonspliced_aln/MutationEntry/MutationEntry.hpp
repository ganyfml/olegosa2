// vim: set noexpandtab tabstop=2:

#pragma once

#include <iostream>
#include <seqan/index.h>
#include <seqan_api/SeqString.hpp>
#include <util/GapAndMM.hpp>
#include <nonspliced_aln/alnNonspliceOpt.hpp>

enum State
{
	STATE_M = 0, STATE_I = 1, STATE_D = 2
};

struct MutationEntry
{
	typedef seqan::Dna5String SeqanString;
	typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
	typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

	MutationEntry(const SeqanSAIter& init_iter)
		: ref_pos(0), pos_offset(0), ref_iter(init_iter), score(0), state(State::STATE_M) {}

	MutationEntry(const MutationEntry& that)
		: ref_pos(that.ref_pos), pos_offset(that.pos_offset), ref_iter(that.ref_iter), score(that.score), state(that.state), gap_mm(that.gap_mm) {}

	SeqanString get_seq() const { return seqan::representative(ref_iter); }
	void display()
	{
		const char stateName[] = {'M', 'I', 'D'};
		printf("Mutation Entry state: %c with ref_pos %lu, pos_offset %lu\n", stateName[state], ref_pos, pos_offset);
		std::cout << "Seq: " << representative(ref_iter) << std::endl;
		gap_mm.display();
	}

	State state;
	SeqanSAIter ref_iter;
	unsigned long ref_pos;
	unsigned long pos_offset;
	int score;
	GapAndMM gap_mm;
};
