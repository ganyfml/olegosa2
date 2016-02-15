// vim: set noexpandtab tabstop=2:
#include <seqan_api.hpp>

using namespace seqan;
using namespace std;

int main(int argc, char ** argv)
{
	string ref_file = argv[1];
	StringSet<CharString> IDSet;
	StringSet<Dna5String> SeqSet;
	SeqFileIn seq_file(toCString(ref_file));
	readRecords(IDSet, SeqSet, seq_file);
	SeqString sequence = value(SeqSet, 0);

	clock_t start1 = clock() ;
	for(int i =0; i< 10000000;++i) {
		auto original = seqan::prefix(sequence, 1);
	}
	clock_t end1 = clock() ;
	double elapsed_time1 = (end1-start1)/(double)CLOCKS_PER_SEC;
	printf("%g\n", elapsed_time1);
	//cerr << elapsed_time1 << endl;

	auto original = seqan::prefix(sequence, 1);
	clock_t start = clock();
	for(int i =0; i< 10000000;++i) {
		SeqString seq = seqan::prefix(sequence, 1);
	}
	clock_t end = clock() ;
	double elapsed_time = (end-start)/(double)CLOCKS_PER_SEC;
	//cout << seq << endl;
	//cerr << elapsed_time << endl;
	printf("%g\n", elapsed_time);
}
