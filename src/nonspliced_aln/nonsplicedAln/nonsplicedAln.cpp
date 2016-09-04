// vim: set noexpandtab tabstop=2:

#include <nonspliced_aln/nonsplicedAln.hpp>
#include <nonspliced_aln/SeqSAIter.hpp>
#include <nonspliced_aln/StateEntry.hpp>
#include <nonspliced_aln/genmu.hpp>
#include <seqan_api/SeqanAPIUtil.hpp>
#include <seqan_api/SeqSuffixArray_conv.hpp>
#include <nonspliced_aln/priority_StateEntry_array.hpp>
#include <nonspliced_aln/MutationTrack.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

bool position_already_in_result(const StateEntry entry, const std::list<AlnResult>& result_list)
{
	for(auto iter = result_list.begin(); iter != result_list.end(); ++iter)
	{
		if(entry.ref_iter.get_SArange().i1 == (*iter).SA_index_low
				&& entry.ref_iter.get_SArange().i2 ==	(*iter).SA_index_high)
		{
			return true;
		}
	}
	return false;
}

void nonsplicedAln(const SeqString& query, std::list<AlnResult>& result_list, const SeqSuffixArray& ref_SAIndex, const alnNonspliceOpt& opt)
{
	std::list<AlnResult> local_result;
	//Change query and ref_SAIndex back to seqan type
	SeqSAIter init_iter(*conv_back(ref_SAIndex));
	std::vector<MutationTrack> mutation_track = gen_query_mutationTracks(query, ref_SAIndex);

	//Init start
	StateEntry init_state_entry(init_iter);
	priority_StateEntry_array se_array(opt);
	se_array.push(init_state_entry, opt);

	StateEntry entry;
	int max_score = opt.max_gapOpen * opt.score_gapOpen + opt.max_gapExt * opt.score_gapExt + opt.max_mismatch * opt.score_mismatch;
	while(se_array.pop_best(entry, max_score))
	{
		int entry_query_pos = entry.query_pos;
		//If the potential has been found
		if(entry_query_pos == query.get_length())
		{
			//DEBUG
			//if(entry.get_seq().get_length() == 0) continue;

			AlnResult r;
			r.num_hits = entry.num_hits();
			seqan::Pair<unsigned> sa_range = entry.get_SArange();
			r.SA_index_high = sa_range.i2;
			r.SA_index_low = sa_range.i1;
			r.seq_length = entry.seq_length();
			r.gap_mm = entry.gap_mm;
			local_result.push_front(r);
			max_score = entry.get_score(opt);
			//END
		}
		else
		{
			bool allow_gap_open_and_ext = true;
			bool allow_mismatch = true;
			int num_mutation_allowed = opt.max_mutation - entry.gap_mm.sum();
			if(mutation_track[entry_query_pos + 1].num_mutation_needed > num_mutation_allowed - 1)
			{
				allow_gap_open_and_ext = false;
			}
			else if(mutation_track[entry_query_pos + 1].num_mutation_needed == num_mutation_allowed - 1
					&& mutation_track[entry_query_pos].num_mutation_needed == num_mutation_allowed - 1 && mutation_track[entry_query_pos - 1].occ == mutation_track[entry_query_pos].occ)
			{
				allow_mismatch = false;
			}

			if(!position_already_in_result(entry, local_result))
			{
				if(allow_gap_open_and_ext)
				{
					//deal with inseration, deletion, mismatch, and match
					if(entry.state == StateEntry::State::STATE_I)
					{
						if(entry.query_pos != 0)
						{
							produceInsertionFromI(entry, se_array, opt);
						}
					}
					else if(entry.state == StateEntry::State::STATE_D)
					{
						produceDeletionFromD(entry, se_array, opt);
					}
					else
					{
						if(entry.query_pos != 0)
						{
							produceInsertionFromM(entry, se_array, opt);
							produceDeletionFromM(entry, se_array, opt);
						}
					}
				}

				produceMatchAndMismatch(entry, se_array, opt, query[entry.query_pos], allow_gap_open_and_ext && allow_mismatch);
			}
		}
	}
	result_list.splice(result_list.end(), local_result);
}
