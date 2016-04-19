// vim: set noexpandtab tabstop=2:

#pragma once

struct alnNonspliceOpt
{
	int max_gapOpen = 0;
	int max_gapExt = 0;
	int max_mismatch = 0;

	bool allow_mismatch = false;
};
