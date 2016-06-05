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
		sense_strand(-1) , colinearity(false), coverage(0), refStart_pos(-1)
		, refEnd_pos(-1), queryStart_pos(-1), queryEnd_pos(-1), score(0) {}

	void display()
	{
		std::cout << "Ref   Start Pos: " << refStart_pos   << ", Ref   End Pos: " << refEnd_pos << std::endl;
		std::cout << "Query Start Pos: " << queryStart_pos << ", Query End Pos: " << queryEnd_pos << std::endl;
		std::cout << "Colinearity: " << colinearity << ", Coverage: " << coverage << std::endl;
		gap_mm.display();
	}

	WordHitsChunkPtr head_chunk;
	WordHitsChunkPtr tail_chunk;
	GapAndMM gap_mm;
	int sense_strand;
	bool colinearity;
	double coverage;
	long refStart_pos;
	long refEnd_pos;
	long queryStart_pos;
	long queryEnd_pos;
	double score;
};

typedef std::shared_ptr<WordHitsChunkBridge> WordHitsChunkBridgePtr;

bool compare_wordHitsChunkBridgeByRefAndStrand(const WordHitsChunkBridgePtr bridge1, const WordHitsChunkBridgePtr& bridge2);
void uniq_wordHitsChunkBridge(std::list<WordHitsChunkBridgePtr>& bridges);
