// vim: set noexpandtab tabstop=2:

#pragma once

#include <queue>
#include <seqan_api/seqString.hpp>
#include <seqan_api/Ref.hpp>

namespace MutationState
{
	enum Value { STATE_M = 0, STATE_I = 1, STATE_D = 2} ;
}

struct MutationGapAndMismatch
{
	int num_mismatch = 0;
	int num_ref_gapOpen = 0;
	int num_ref_gapExt = 0;
	int num_query_gapOpen = 0;
	int num_query_gapExt = 0;

	int get_numGapOpen() const { return (num_ref_gapOpen + num_query_gapOpen); }
	int get_numGapExt() const { return (num_ref_gapExt + num_query_gapExt); }
	int get_numDiff() const { return (this->get_numGapOpen() + this->get_numGapExt()); }

	int cal_alnScore(int score_mismatch, int score_gapOpen, int score_gapExtension) const
	{
		return num_mismatch * score_mismatch + this->get_numGapOpen() * score_gapOpen + this->get_numGapExt() * score_gapExtension;
	}
};

class MutationEntry
{
	int index_;
	int score_;
	MutationState::Value state_;

	public:
	MutationGapAndMismatch gap_mm;
	SeqString seq;

	MutationEntry(SeqString seq)
		: index_(0)
			, state_(MutationState::STATE_M)
			 , seq(seq)
			 , score_(0)
	{}

	int get_index() const { return index_; }

	int get_state() const { return state_; }

	int get_score() const { return score_; }

	int get_seqLength() const { return ::get_seqLength(seq); }

	void set_score(int score_mismatch, int score_gapOpen, int score_gapExtension)
	{
		score_ = gap_mm.cal_alnScore(score_mismatch, score_gapOpen, score_gapExtension);
	}

	void change_state(MutationState::Value state) { state_ = state; }

	void increase_index() { ++index_; }

	bool exist_inRef(const Ref& ref) const { return ref.find_exist(seq); }

	bool allow_gapOpen(int max_gapOpen) const
	{
		return gap_mm.get_numGapOpen() <= max_gapOpen;
	}

	bool allow_gapExt(int max_gapExt) const
	{
		return gap_mm.get_numGapExt() <= max_gapExt;
	}

	bool allow_diff(int max_diff) const
	{
		return gap_mm.get_numDiff() <= max_diff; 
	}

	bool operator<(const MutationEntry& second) const 
	{
		if(this->seq == second.seq && this->index_ == second.index_ && this->score_ == second.score_)
		{
			return false;
		}
		else
		{
			return this->score_ >= second.score_;
		}
	}

};

typedef std::shared_ptr<MutationEntry> MutationPtr;
typedef std::set<MutationEntry> MutationSet;

struct regularSearchOpt{
	int score_mismatch = 1;
	int score_gapOpen = 1;
	int score_gapExtension = 1;

	int max_gapOpen = 2;
	int max_gapExt = 6;
	int max_mismatch = 5;
	int max_diff = 10;

	bool allow_mismatch = true;
};

int aln_nonsplice(const Ref& reference, const SeqString& query, const regularSearchOpt& opt);
