// vim: set noexpandtab tabstop=2:

#pragma once

#include <spliced_aln/WordHit.hpp>
#include <seqan_api/SeqSuffixArray.hpp>
#include <util/GapAndMM.hpp>
#include <iostream>

namespace ExtendDirection
{
	enum Value {left = 0, right = 1, both = 2};
}

struct WordHitsChunk
{
	WordHitsChunk(int id) :
		id(id), strand(-1), is_first(true), is_last(true)
		, colinearity(false), coverage(0), refStart_pos(-1), refEnd_pos(-1)
		, queryStart_pos(-1), queryEnd_pos(-1) {}

	void display()
	{
		std::cout << "WordChunk ID: " << id << ", with strand: " << strand << ", containing " << wordHitList.size() << " wordHits" << std::endl;
		std::cout << "Ref   Start Pos: " << refStart_pos   << ", Ref   End Pos: " << refEnd_pos << std::endl;
		std::cout << "Query Start Pos: " << queryStart_pos << ", Query End Pos: " << queryEnd_pos << std::endl;
		std::cout << "Colinearity: " << colinearity << ", Coverage: " << coverage << std::endl;
		gapMM.display();
	}

	GapAndMM gapMM;
	int id;
	int strand;
	bool is_first;
	bool is_last;
	bool colinearity;
	double coverage;
	long refStart_pos;
	long refEnd_pos;
	long queryStart_pos;
	long queryEnd_pos;
	std::list<WordHitPtr> wordHitList;

	void extend_inexact_left(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore);
	void extend_inexact_right(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore);
	void extend_inexact(const SeqString& query, const SeqSuffixArray& ref_SAIndex, bool stop_atNegativeScore, ExtendDirection::Value direction);
};

typedef std::shared_ptr<WordHitsChunk> WordHitsChunkPtr;
