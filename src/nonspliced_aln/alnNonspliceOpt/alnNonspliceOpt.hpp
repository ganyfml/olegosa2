// vim: set noexpandtab tabstop=2:

#pragma once

struct alnNonspliceOpt
{
	int max_gapOpen = 0;
	int max_gapExt = 0;
	int max_mismatch = 0;
	int max_mutation = 0;

	int score_gapOpen = 11;
	int score_gapExt = 4;
	int score_mismatch = 3; 
};
