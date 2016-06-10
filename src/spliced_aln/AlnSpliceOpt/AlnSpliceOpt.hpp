// vim: set noexpandtab tabstop=2:

#pragma once

namespace Strand_mode
{
	enum Value {forward = 0, reverse = 1, disable = -1};
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
	bool report_best_only = true;
	Strand_mode::Value strand_mode = Strand_mode::disable;
};
