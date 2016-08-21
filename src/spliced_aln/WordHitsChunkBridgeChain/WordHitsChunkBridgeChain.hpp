// vim: set noexpandtab tabstop=2:

#pragma once

#include <util/GapAndMM.hpp>
#include <spliced_aln/WordHitsChunkBridge.hpp>
#include <list>

struct WordHitsChunkBridgeChain
{
	int strand;
	int spliced_strand;
	double logistic_prob;

	GapAndMM gap_mm;
	int num_diff;

	long start_pos_in_ref;
	long end_pos_in_ref;
	long start_pos_in_query;
	long end_pos_in_query;
	std::list<WordHitsChunkBridgePtr> bridges;

	void summarize(bool global, int query_length);

	void display()
	{
		printf("Chunk Strand: %d, Spliced Strand: %d\n", strand, spliced_strand);
		printf("Location:\n");
		printf("Ref   Start: %ld, Ref   End: %ld\n", start_pos_in_ref, end_pos_in_ref);
		printf("Query Start: %ld, Query End: %ld\n", start_pos_in_query, end_pos_in_query);
	}
};

typedef std::shared_ptr<WordHitsChunkBridgeChain> WordHitsChunkBridgeChainPtr;

bool is_identical(const WordHitsChunkBridgeChainPtr& first, const WordHitsChunkBridgeChainPtr& second);

void summarize_WordHitsChunkBridgeChains(std::list<WordHitsChunkBridgeChainPtr>& results, int query_length, bool global);
