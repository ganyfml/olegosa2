// vim: set noexpandtab tabstop=2:

#include "../../../splicedAln.hpp"
#include <seqan_api/SeqStringSet.hpp>
#include <seqan_api/CharStringSet.hpp>

using namespace std;

int main(int, char* argv[])
{
	string queryFileName(argv[1]);
	SeqStringSet query_seqs;
	CharStringSet query_ids;
	CharStringSet query_quals;
	load_seqs_with_qual(queryFileName, query_seqs, query_ids, query_quals);

	//Construct ref_SA
	std::string ref_in(argv[2]);
	SeqSuffixArray ref_SA(ref_in);

	cout << "loading complete!" << endl;
	AlnSpliceOpt opt;
	for(int j = 0; j < query_seqs.get_length(); ++j)
	{
		SeqString query_seq = query_seqs[j];
		opt.word_length = 5;
		opt.word_max_overlap = 0;
		opt.min_anchor_size = 3;

		splicedAln(query_seq, ref_SA, opt);
	}
}
