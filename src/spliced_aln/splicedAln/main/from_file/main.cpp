// vim: set noexpandtab tabstop=2:

#include "../../splicedAln.hpp"

using namespace std;

int main()
{
	string queryFileName("./query.fa");
	SeqString query_seq;
	CharString query_id;
	load_seq(queryFileName, query_seq, query_id);

	string refFileName("./ref.fq");
	SeqString ref_seq;
	CharString ref_id;
	load_seq(refFileName, ref_seq, ref_id);

	//Construct ref_SA
	SeqSuffixArray ref_SA(ref_seq);

	AlnSpliceOpt opt;
	opt.word_length = 5;
	opt.word_max_overlap = 0;
	opt.min_anchor_size = 3;

	splicedAln(query_seq, ref_SA, opt);
}
