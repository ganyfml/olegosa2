// vim: set noexpandtab tabstop=2:

//Debug
#include <valgrind/callgrind.h>
//End

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
	CALLGRIND_TOGGLE_COLLECT;
	//Debug
#include <ctime>
	std::clock_t    start;
	start = std::clock();
	//End
	for(int j = 0; j < query_seqs.get_length(); ++j)
	{
		SeqString query_seq = query_seqs[j];
		opt.word_length = 15;
		opt.word_max_overlap = 0;
		opt.min_anchor_size = 8;

		splicedAln(query_seq, ref_SA, opt);
	}
	//Debug
	std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
	//End
	CALLGRIND_TOGGLE_COLLECT;
	CALLGRIND_DUMP_STATS;
}
