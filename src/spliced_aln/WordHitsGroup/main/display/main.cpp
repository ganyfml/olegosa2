// vim: set noexpandtab tabstop=2:

#include "../../WordHitsGroup.hpp"
#include <seqan_api/SeqString.hpp>

using namespace std;

int main()
{
	int hit_id = 0;
	WordHitPtr hit = make_shared<WordHit>(hit_id);

	int word_group_id = 0;
	WordHitsGroupPtr wordhitsgroup = make_shared<WordHitsGroup>(word_group_id);
	wordhitsgroup->score = 1.5;
	wordhitsgroup->wordhits.push_back(hit);

	wordhitsgroup->display();
}
