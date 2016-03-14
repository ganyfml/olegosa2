// vim: set noexpandtab tabstop=2:

#pragma once;

#include <seqan_api/SeqString.hpp>
#include <seqan_api/Ref.hpp>
#include <set>

namespace MutationState
{
	enum Value { STATE_M = 0, STATE_I = 1, STATE_D = 2} ;
}


struct MutationGapAndMismatch
{
	private:
	int num_mismatch_ = 0;
	int num_ref_gapOpen_ = 0;
	int num_ref_gapExt_ = 0;
	int num_query_gapOpen_ = 0;
	int num_query_gapExt_ = 0;

	public:
	int get_numGapOpen() const { return (num_ref_gapOpen_ + num_query_gapOpen_); }
	int get_numGapExt() const { return (num_ref_gapExt_ + num_query_gapExt_); }
	int get_numDiff() const { return (get_numGapOpen() + get_numGapExt()); }
	int cal_alnScore(int score_mismatch, int score_gapOpen, int score_gapExtension) const
	{
		return num_mismatch_ * score_mismatch + get_numGapOpen() * score_gapOpen + get_numGapExt() * score_gapExtension;
	}
};

typedef std::set<MutationEntry> MutationSet;

class MutationEntry
{
	int query_index_;
	int score_;
	MutationState::Value state_;
	MutationGapAndMismatch gap_mm_;
	SeqString seq_;

	public:
	MutationEntry(SeqString seq)
		: query_index_(0)
			, state_(MutationState::STATE_M)
			 , seq_(seq)
			 , score_(0) {}

	void produce_insertion(const SeqString& original, const Ref& ref, MutationSet& set);
	void produce_deletion(const SeqString& original, const Ref& ref, MutationSet& set);
	void produce_mismatch(const SeqString& original, const Ref& ref, MutationSet& set);

	private:
	void set_score(int score_mismatch, int score_gapOpen, int score_gapExtension)
	{
		score_ = gap_mm.cal_alnScore(score_mismatch, score_gapOpen, score_gapExtension);
	}

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
