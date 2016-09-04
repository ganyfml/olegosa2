// vim: set noexpandtab tabstop=2:

#include <nonspliced_aln/exactMatchAln.hpp>
#include <seqan_api/SeqSuffixArray_conv.hpp>
#include <seqan_api/SeqString.hpp>
#include <seqan_api/SeqString_conv.hpp>
#include <nonspliced_aln/SeqSAIter.hpp>
#include <seqan/index.h>

void exactMatchAln(const SeqString& query, std::list<AlnResult>& result_list, const SeqSuffixArray& ref_SAIndex, const alnNonspliceOpt& opt)
{
	typedef seqan::Dna5String SeqanString;
	typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
	typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

	SeqanSAIter seqan_sa_iter(*conv_back(ref_SAIndex));
	if(goDown(seqan_sa_iter, *conv_back(query)))
	{
		AlnResult r;
		seqan::Pair<unsigned> sa_range = range(seqan_sa_iter);
		r.SA_index_high = sa_range.i2;
		r.SA_index_low = sa_range.i1;
		r.num_hits = countOccurrences(seqan_sa_iter);
		r.seq_length = query.get_length();
		result_list.push_front(r);
	}
}
