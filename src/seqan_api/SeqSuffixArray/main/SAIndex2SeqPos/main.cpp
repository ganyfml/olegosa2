// vim: set noexpandtab tabstop=2:
#include "../../SeqSuffixArray.hpp"
#include <seqan_api/SeqSuffixArray_conv.hpp>
#include <seqan/index.h>
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
	typedef seqan::Dna5String SeqanString;
	typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
	typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

	SeqString ref((string(argv[1])));
	SeqString query((string(argv[2])));
	SeqSuffixArray ref_SA(ref);

	//Get the SA index for query
	SeqanSA sa_ref = *conv_back(ref_SA);
	SeqanSAIter sa_iter(sa_ref);
	for(int i = 0; i < query.get_length(); ++i)
	{
		goDown(sa_iter, query[i]);
	}
	seqan::Pair<unsigned> sa_range = range(sa_iter);
	int query_RefSAIndexLow = sa_range.i1;
	int query_RefSAIndexHigh = sa_range.i2;
	printf("Ref SA Index: %d, %d\n", query_RefSAIndexLow, query_RefSAIndexHigh);

	//Get the query back based on its length and SA index
	printf("Query appeared in Ref pos: %lu\n", ref_SA.SAIndex2SeqPos(query_RefSAIndexLow));
}
