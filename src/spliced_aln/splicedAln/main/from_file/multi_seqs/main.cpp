// vim: set noexpandtab tabstop=2:

#include "../../../splicedAln.hpp"
#include <seqan_api/SeqStringSet.hpp>
#include <seqan_api/CharStringSet.hpp>

using namespace std;

int main()
{
	string queryFileName("./querys.fa");
	SeqStringSet query_seqs;
	CharStringSet query_ids;
	load_seqs(queryFileName, query_seqs, query_ids);

	string refFileName("./refs.fq");
	SeqStringSet ref_seqs;
	CharStringSet ref_ids;
	load_seqs(refFileName, ref_seqs, ref_ids);

	for(int i = 0; i < ref_seqs.get_length(); ++i)
	{
		//Construct ref_SA
		SeqString ref_seq = ref_seqs[i];
		SeqSuffixArray ref_SA(ref_seq);
		for(int j = 0; j < query_seqs.get_length(); ++j)
		{
			SeqString query_seq = query_seqs[j];
			AlnSpliceOpt opt;
			opt.word_length = 5;
			opt.word_max_overlap = 0;
			opt.min_anchor_size = 3;

			splicedAln(query_seq, ref_SA, opt);
		}
	}
}
