// vim: set noexpandtab tabstop=2:

#pragma once

#include <spliced_aln/WordHit.hpp>
#include <spliced_aln/AlnSpliceOpt.hpp>
#include <spliced_aln/WordHitsChunk.hpp>
#include <seqan_api/SeqSuffixArray.hpp>
#include <util/GapAndMM.hpp>
#include <iostream>

struct WordHitsChunkBridge
{
	WordHitsChunkBridge() :
		sense_strand(-1) , start_pos_in_ref(-1) , end_pos_in_ref(-1)
		, start_pos_in_query(-1), end_pos_in_query(-1), score(0) {}

	void display()
	{
		std::cout << "Ref   Start Pos: " << start_pos_in_ref   << ", Ref   End Pos: " << end_pos_in_ref << std::endl;
		std::cout << "Query Start Pos: " << start_pos_in_query << ", Query End Pos: " << end_pos_in_query << std::endl;
		gap_mm.display();
	}

	WordHitsChunkPtr head_chunk;
	WordHitsChunkPtr tail_chunk;
	GapAndMM gap_mm;
	int adjust_diff;
	int sense_strand;
	long start_pos_in_ref;
	long end_pos_in_ref;
	long start_pos_in_query;
	long end_pos_in_query;
	double score;
};

typedef std::shared_ptr<WordHitsChunkBridge> WordHitsChunkBridgePtr;
