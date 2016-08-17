// vim: set noexpandtab tabstop=2:

#pragma once

#include <util/GapAndMM.hpp>
#include <spliced_aln/WordHitsChunkBridge.hpp>
#include <list>

struct SplicedAlnResult
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

	void evaluate(bool global, int query_length);

	void display()
	{
		printf("Strand: %d, Sense Strand: %d, logistic prob: %f\n", strand, spliced_strand, logistic_prob);
		printf("Location:\n");
		printf("Ref   Start: %ld, Ref   End: %ld\n", start_pos_in_ref, end_pos_in_ref);
		printf("Query Start: %ld, Query End: %ld\n", start_pos_in_query, end_pos_in_query);
		printf("Gap And MM:\n");
		printf("num diff: %d\n", num_diff);
		gap_mm.display();
	}
};

typedef std::shared_ptr<SplicedAlnResult> SplicedAlnResultPtr;

bool is_identical(const SplicedAlnResultPtr& first, const SplicedAlnResultPtr& second);

void evaluate_SplicedAlnResults(std::list<SplicedAlnResultPtr>& results, int query_length, bool global);
