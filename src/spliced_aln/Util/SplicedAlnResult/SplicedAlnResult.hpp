// vim: set noexpandtab tabstop=2:

#pragma once

#include <util/GapAndMM.hpp>
#include <spliced_aln/WordHitsChunkBridge.hpp>

struct SplicedAlnResult
{
  GapAndMM gap_mm;
  int query_strand;
  int sense_strand;
  double logistic_prob;

  long refStart_pos;
  long refEnd_pos;
  long queryStart_pos;
  long queryEnd_pos;
	std::list<WordHitsChunkBridgePtr> bridges;
};

typedef std::shared_ptr<SplicedAlnResult> SplicedAlnResultPtr;
