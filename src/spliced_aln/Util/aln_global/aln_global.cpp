#include <spliced_aln/aln_global.hpp>
#include <seqan/align.h>
#include <seqan_api/SeqanAPIUtil.hpp>
#include <iostream>

using namespace seqan;
using namespace std;

int aln_global(const SeqString& ref_part, const SeqString& query_part, GapAndMM& gap_mm)
{
	typedef Dna5String SeqanString;
	typedef Gaps<SeqanString, ArrayGaps> TGaps;
	typedef Iterator<TGaps>::Type TGapsIterator;

	TGaps gap_query;
	TGaps gap_ref;
	assignSource(gap_query, *constVoid2localType<SeqanString>(query_part.get_pointer()));
	assignSource(gap_ref, *constVoid2localType<SeqanString>(ref_part.get_pointer()));

	// Restirct search space using a band allowing at most 2 errors in vertical/horizontal direction.

	//TODO USE BWA SCORE MATRIX
	globalAlignment(gap_query, gap_ref, Score<int>(0, -1, -1), AlignConfig<false, false, false, false>(), -1, 1);

	// Reinitilaize the iterators.
	TGapsIterator it_gaps_ref = begin(gap_ref);
	TGapsIterator it_gaps_query = begin(gap_query);

	it_gaps_ref = begin(gap_ref);
	it_gaps_query = begin(gap_query);

	int numChar;
	while(it_gaps_query != end(gap_query))
	{
		// Count insertions.
		if(isGap(it_gaps_query))
		{
			int numGaps = countGaps(it_gaps_query);
			gap_mm.num_gapOpenQuery += 1;
			gap_mm.num_gapExtQuery += numGaps;
			it_gaps_query += numGaps;
			it_gaps_ref += numGaps;
			continue;
		}
		// Count deletions.
		if(isGap(it_gaps_ref))
		{
			int numGaps = countGaps(it_gaps_ref);
			gap_mm.num_gapOpenRef += 1;
			gap_mm.num_gapExtRef += numGaps;
			it_gaps_query += numGaps;
			it_gaps_ref += numGaps;
			continue;
		}
		// Count matches.
		while(*it_gaps_ref == *it_gaps_query && it_gaps_query != end(gap_query))
		{
			++numChar;
			++it_gaps_query;
			++it_gaps_ref;
		}
		if(numChar != 0)
		{
			numChar = 0;
			continue;
		}
		// Count mismatches.
		while (*it_gaps_ref != *it_gaps_query && it_gaps_query != end(gap_query))
		{
			++numChar;
			++it_gaps_query;
			++it_gaps_ref;
		}
		if (numChar != 0)
		{
			gap_mm.num_mismatch += numChar;
		}
		numChar = 0;
	}

	return 0;
}
