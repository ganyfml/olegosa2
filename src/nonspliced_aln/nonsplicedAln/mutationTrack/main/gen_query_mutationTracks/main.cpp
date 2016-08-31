// vim: set noexpandtab tabstop=2:

#include "../../MutationTrack.hpp"

using namespace std;

int main(int, char* argv[])
{
  SeqString ref_seq((string(argv[1])));
  SeqSuffixArray ref_SA(ref_seq);

  SeqString query_seq((string(argv[2])));
	std::vector<MutationTrack> mutation_track = gen_query_mutationTracks(query_seq, ref_SA);

	for(int i = 0; i < (int)mutation_track.size(); ++i)
	{
		printf("index: %d\n", i);
		printf("occ: %ld, num_mutation_needed: %d\n", mutation_track[i].occ, mutation_track[i].num_mutation_needed);
	}
}
