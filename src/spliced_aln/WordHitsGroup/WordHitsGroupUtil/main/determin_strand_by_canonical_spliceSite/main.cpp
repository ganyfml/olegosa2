// vim: set noexpandtab tabstop=2:

#include "../../WordHitsGroupUtil.hpp"
#include <map>
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
	SeqString ref = string(argv[1]);
	SeqSuffixArray ref_SAIndex(ref);

	long donor_pos = atoi(argv[2]);
	long acceptor_pos = atoi(argv[3]);


	std::map<int, string> strand_info;

	strand_info[1] = "forward";
	strand_info[0] = "none_decide";
	strand_info[-1] = "reverse";

	Strand::Value result_strand = determin_strand_by_canonical_spliceSite(ref_SAIndex, donor_pos, acceptor_pos);
	cout << strand_info[result_strand] << endl;
}
