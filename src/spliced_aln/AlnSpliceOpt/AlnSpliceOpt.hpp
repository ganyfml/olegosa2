// vim: set noexpandtab tabstop=2:

#pragma once

struct AlnSpliceOpt
{
	int word_length = 0;
	int word_max_overlap = 0;
	int wordChunk_max_diff = 0;
	int max_overhang = 6;
	int max_intron_size = 500000;
	bool denovo_search = 1;
};
