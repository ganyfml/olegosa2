// vim: set noexpandtab tabstop=2:

#include "../../WordHitsGroup.hpp"
#include <seqan_api/SeqString.hpp>

using namespace std;

int main(int, char* argv[])
{
	int word_group1_id = 1;
	WordHitsGroupPtr wordhitsgroup1 = make_shared<WordHitsGroup>(word_group1_id);
	wordhitsgroup1->score = atof(argv[1]);

	int word_group2_id = 2;
	WordHitsGroupPtr wordhitsgroup2 = make_shared<WordHitsGroup>(word_group2_id);
	wordhitsgroup2->score = atof(argv[2]);

	cout << compare_wordHitsGroupByScore(wordhitsgroup1, wordhitsgroup2) << endl;
}
