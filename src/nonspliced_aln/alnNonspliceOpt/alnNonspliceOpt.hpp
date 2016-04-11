// vim: set noexpandtab tabstop=2:

#pragma once

struct alnNonspliceOpt
{
	int score_mismatch = 1;
	int score_gapOpen = 1;
	int score_gapExtension = 1;

	int max_gapOpen = 1;
	int max_gapExt = 3;
	int max_mismatch = 5;
	int max_diff = 4;

	bool allow_mismatch = true;
};
