// vim: set noexpandtab tabstop=2:

#pragma once

#include <util/GapAndMM.hpp>
#include <spliced_aln/WordHitsChunkBridge.hpp>

struct SplicedAlnResult
{
	int strand;
	int sense_strand;
	double logistic_prob;

	GapAndMM gap_mm;
	int num_diff;

	long refStart_pos;
	long refEnd_pos;
	long queryStart_pos;
	long queryEnd_pos;
	std::list<WordHitsChunkBridgePtr> bridges;

	void evaluate(bool global, int query_length);

	void display()
	{
		printf("Strand: %d, Sense Strand: %d, logistic prob: %f\n", strand, sense_strand, logistic_prob);
		printf("Location:\n");
		printf("Ref   Start: %ld, Ref   End: %ld\n", refStart_pos, refEnd_pos);
		printf("Query Start: %ld, Query End: %ld\n", queryStart_pos, queryEnd_pos);
		printf("Gap And MM:\n");
		printf("num diff: %d\n", num_diff);
		gap_mm.display();
	}
};

typedef std::shared_ptr<SplicedAlnResult> SplicedAlnResultPtr;

bool is_identical(const SplicedAlnResultPtr& first, const SplicedAlnResultPtr& second);
