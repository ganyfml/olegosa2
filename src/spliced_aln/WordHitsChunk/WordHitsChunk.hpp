// vim: set noexpandtab tabstop=2:

#pragma once

#include <spliced_aln/WordHit.hpp>
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <seqan_api/SeqSuffixArray.hpp>
#include <util/GapAndMM.hpp>
#include <spliced_aln/Util.hpp>
#include <iostream>

namespace ExtendDirection
{
	enum Value {left = 1, right = 2, both = 3};
}

struct WordHitsChunk
{
	WordHitsChunk(int id) :
		id(id), strand(Strand::none_decide) , hit_refPosNonDec(false), coverage(0)
		, start_pos_in_ref(-1), end_pos_in_ref(-1) , start_pos_in_query(-1), end_pos_in_query(-1) {}

	WordHitsChunk(
			Strand::Value strand
			, long start_pos_in_ref, long end_pos_in_ref
			, int start_pos_in_query, int end_pos_in_query) :
		id(-1), strand(strand) , hit_refPosNonDec(true), coverage(1)
		, start_pos_in_ref(start_pos_in_ref), end_pos_in_ref(end_pos_in_ref)
		, start_pos_in_query(start_pos_in_query), end_pos_in_query(end_pos_in_query) {}

	void display()
	{
		std::cout << "WordChunk ID: " << id << ", with strand: " << strand << ", containing " << wordHitList.size() << " wordHits" << std::endl;
		std::cout << "Ref   Start Pos: " << start_pos_in_ref   << ", Ref   End Pos: " << end_pos_in_ref << std::endl;
		std::cout << "Query Start Pos: " << start_pos_in_query << ", Query End Pos: " << end_pos_in_query << std::endl;
		std::cout << "Hit refPos Non-Dec: " << hit_refPosNonDec << ", Coverage: " << coverage << std::endl;
		gapMM.display();
	}

	void display_pos()
	{
		std::cout << "Ref   Start Pos: " << start_pos_in_ref   << ", Ref   End Pos: " << end_pos_in_ref << std::endl;
		std::cout << "Query Start Pos: " << start_pos_in_query << ", Query End Pos: " << end_pos_in_query << std::endl;
	}

	GapAndMM gapMM;
	int id;
	Strand::Value strand;
	bool hit_refPosNonDec;
	bool is_first_in_bridge;
	bool is_last_in_bridge;
	double coverage;
	long start_pos_in_ref;
	long end_pos_in_ref;
	int start_pos_in_query;
	int end_pos_in_query;
	std::list<WordHitPtr> wordHitList;

	void summarize(int word_size, Strand::Value hit_strand);
	void extend_inexact(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore, ExtendDirection::Value direction);
	void extend_inexact_left(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore);
	void extend_inexact_right(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore);
};

typedef std::shared_ptr<WordHitsChunk> WordHitsChunkPtr;

bool compare_wordHitsChunkByRefPos(const WordHitsChunkPtr chunk1, const WordHitsChunkPtr chunk2);
