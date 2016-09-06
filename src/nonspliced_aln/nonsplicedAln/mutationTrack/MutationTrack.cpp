// vim: set noexpandtab tabstop=2:

#include <nonspliced_aln/MutationTrack.hpp>

std::vector<MutationTrack> gen_query_mutationTracks(const SeqString& query, const SeqSuffixArray& ref_SAIndex)
{
	SeqSAIter iter(*conv_back(ref_SAIndex));
	std::vector<MutationTrack> query_mutationTracks(query.get_length() + 1);

	int num_mutation_needed = 0;
	for(int i = 0; i < query.get_length(); ++i)
	{
		MutationTrack query_mutaion_track_pos_i;
		if(iter.godown_char(query[i]))
		{
			query_mutaion_track_pos_i.occ = iter.num_occ();
			query_mutaion_track_pos_i.num_mutation_needed = num_mutation_needed;
		}
		else
		{
			iter.reset();
			query_mutaion_track_pos_i.occ = iter.num_occ();
			query_mutaion_track_pos_i.num_mutation_needed = ++num_mutation_needed;
		}
		query_mutationTracks[i + 1] = query_mutaion_track_pos_i;
	}
	query_mutationTracks[0].num_mutation_needed = num_mutation_needed + 1; 
	query_mutationTracks[0].occ = 0;

	for(int i = 1; i <= query.get_length(); ++i)
	{
		query_mutationTracks[i].num_mutation_needed = query_mutationTracks[query.get_length() - 1].num_mutation_needed - query_mutationTracks[i].num_mutation_needed;
	}

	return query_mutationTracks;
}
