// vim: set noexpandtab tabstop=2:

#pragma once

#include <queue>
#include <seqan/index.h>
#include <seqan_api/SeqString.hpp>
#include <util/GapAndMM.hpp>
#include <nonspliced_aln/aln_nonspliceOpt.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

class MutationEntry
{
	public:
		enum State
		{
			STATE_M = 0, STATE_I = 1, STATE_D = 2
		};

		MutationEntry(const SeqanSAIter& init_iter)
			: ref_pos(0), ref_iter(init_iter), score(0), state(State::STATE_M) {}

		MutationEntry(const MutationEntry& that)
			: ref_pos(that.ref_pos), ref_iter(that.ref_iter), gap_mm(that.gap_mm)
			  , score(that.score), state(that.state) {}

		void produceInsertion(std::queue<MutationEntry>& mutation_queue, aln_nonspliceOpt opt);
		void produceDeletion(std::queue<MutationEntry>& mutation_queue, aln_nonspliceOpt opt);
		void produceMismatch(std::queue<MutationEntry>& mutation_queue, aln_nonspliceOpt opt, char next_char);
		void produceMatch(std::queue<MutationEntry>& mutation_queue, aln_nonspliceOpt opt, char next_char);

		//Public due to test purpose
		State state;

	private:
		SeqanSAIter ref_iter;
		unsigned long ref_pos;
		int score;
		GapAndMM gap_mm;
};

