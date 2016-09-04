// vim: set noexpandtab tabstop=2:

#include <string>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <nonspliced_aln/nonsplicedAln.hpp>
#include <util/AlnResult.hpp>
#include <seqan/bam_io.h>
#include <util/OutputWriter.hpp>

using namespace std;

int main(int, char* argv[])
{
	SeqString query_seq((string(argv[2])));
	SeqString ref_seq((string(argv[1])));
	CharString query_qual((string(argv[3])));
	CharString ref_name((string("chr_name")));
	SeqSuffixArray ref_index(ref_seq);

	alnNonspliceOpt aln_opt;
	aln_opt.max_gapExt = atoi(argv[4]);
	aln_opt.max_gapOpen = atoi(argv[5]);
	aln_opt.max_mismatch = atoi(argv[6]);
	queue<AlnResult> results;
	nonsplicedAln(query_seq, results, ref_index, aln_opt);

	SAMWritter sam_file;
	while(!results.empty())
	{
		AlnResult result = results.front();
		results.pop();
		for(unsigned long i = result.SA_index_low; i < result.SA_index_high; ++i)
		{
			seqan::String<seqan::CigarElement<> > cigar;
			sam_file.write_record(query_seq, i, result.seq_length, ref_index, ref_name, false, query_qual);
		}
	}
}
