// vim: set noexpandtab tabstop=2:

#pragma once

#include <spliced_aln/WordHit.hpp>
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqSuffixArray.hpp>
#include <util/GapAndMM.hpp>
#include <iostream>

namespace ExtendDirection
{
	enum Value {left = 1, right = 2, both = 3};
}

namespace Strand
{
	enum Value {forward = 1, reverse = -1, none_decide = 0};
}

struct WordHitsChunk
{
	WordHitsChunk(int id) :
		id(id), strand(Strand::none_decide) , hit_refPosNonDec(false), coverage(0)
		, start_pos_in_ref(-1), end_pos_in_ref(-1) , start_pos_in_query(-1), end_pos_in_query(-1) {}

	void display()
	{
		std::cout << "WordChunk ID: " << id << ", with strand: " << strand << ", containing " << wordHitList.size() << " wordHits" << std::endl;
		std::cout << "Ref   Start Pos: " << start_pos_in_ref   << ", Ref   End Pos: " << end_pos_in_ref << std::endl;
		std::cout << "Query Start Pos: " << start_pos_in_query << ", Query End Pos: " << end_pos_in_query << std::endl;
		std::cout << "Hit refPos Non-Dec: " << hit_refPosNonDec << ", Coverage: " << coverage << std::endl;
		gapMM.display();
	}

	GapAndMM gapMM;
	int id;
	Strand::Value strand;
	bool hit_refPosNonDec;
	double coverage;
	long start_pos_in_ref;
	long end_pos_in_ref;
	long start_pos_in_query;
	long end_pos_in_query;
	std::list<WordHitPtr> wordHitList;

	void evaluate(int word_size, Strand::Value hit_strand);
	void extend_inexact(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore, ExtendDirection::Value direction);
	void extend_inexact_left(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore);
	void extend_inexact_right(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore);
};

typedef std::shared_ptr<WordHitsChunk> WordHitsChunkPtr;

bool compare_wordHitsChunkByRefPos(const WordHitsChunkPtr chunk1, const WordHitsChunkPtr chunk2);
