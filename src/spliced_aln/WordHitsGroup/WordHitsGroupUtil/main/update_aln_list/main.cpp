// vim: set noexpandtab tabstop=2:

#include "../../WordHitsGroupUtil.hpp"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main()
{
	int aln_length = 2;
	WordHitsChunkBridgeChainPtr r1 = make_shared<WordHitsChunkBridgeChain>();
	WordHitsChunkBridgeChainPtr r2 = make_shared<WordHitsChunkBridgeChain>();

	list<WordHitsChunkBridgeChainPtr> results;
	results.push_back(r1);
	results.push_back(r2);

	vector<bool> destroy_flag{true, false};
	update_aln_list(results, destroy_flag, aln_length);

	printf("results size: %ld, aln_lenth: %d\n", results.size(), aln_length);
}
