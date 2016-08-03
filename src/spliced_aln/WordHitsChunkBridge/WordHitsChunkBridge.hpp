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
	WordHitsChunkBridge(WordHitsChunkPtr head_chunk, WordHitsChunkPtr tail_chunk, long start_pos_in_ref, long end_pos_in_ref
			, int start_pos_in_query, int end_pos_in_query, int spliced_strand, GapAndMM gap_mm, int original_search_area_diff) :
		head_chunk(head_chunk) , tail_chunk(tail_chunk), start_pos_in_ref(start_pos_in_ref) , end_pos_in_ref(end_pos_in_ref)
		, start_pos_in_query(start_pos_in_query), end_pos_in_query(end_pos_in_query), spliced_strand(spliced_strand), gap_mm(gap_mm)
		, original_search_area_diff(original_search_area_diff) {}

	void display()
	{
		std::cout << "Ref   Start Pos: " << start_pos_in_ref   << ", Ref   End Pos: " << end_pos_in_ref << std::endl;
		std::cout << "Query Start Pos: " << start_pos_in_query << ", Query End Pos: " << end_pos_in_query << std::endl;
		gap_mm.display();
		std::cout << "original_search_area_diff: " << original_search_area_diff << std::endl;
	}

	WordHitsChunkPtr head_chunk;
	WordHitsChunkPtr tail_chunk;
	long start_pos_in_ref;
	long end_pos_in_ref;
	long start_pos_in_query;
	long end_pos_in_query;
	int spliced_strand;
	GapAndMM gap_mm;
	int original_search_area_diff;
	double score;
};

typedef std::shared_ptr<WordHitsChunkBridge> WordHitsChunkBridgePtr;
