// vim: set noexpandtab tabstop=2:

#pragma once

namespace Strand_mode
{
	enum Value {both = 3, forward = 1, reverse = 2};
}

struct AlnSpliceOpt
{
	int word_length = 0;
	int word_max_overlap = 0;
	int wordChunk_max_diff = 0;
	int max_overhang = 6;
	int max_intron_size = 500000;
	int min_intron_size = 4;
	bool denovo_search = 1;
	int min_anchor_size = 8;
	int min_exon_size = 9;
	int local_wordChunk_diff = 2; //local_wordChunk_diff = (opt.wordChunk_max_diff > 2) ? 2 : opt.wordChunk_max_diff;
	bool report_best_only = true;
	Strand_mode::Value strand_mode = Strand_mode::both;
};
