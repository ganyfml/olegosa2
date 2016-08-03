// vim: set noexpandtab tabstop=2:

#include "../../WordHitsGroupUtil.hpp"
#include <iostream>

using namespace std;

int main(int, char* argv[])
{
	SpliceType::Value splice_type = static_cast<SpliceType::Value>(atoi(argv[1]));
	Strand::Value splice_strand = static_cast<Strand::Value>(atoi(argv[2]));
	cout << get_partner_splice_site(splice_type, splice_strand) << endl;
}
