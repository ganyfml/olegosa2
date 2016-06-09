// vim: set noexpandtab tabstop=2:

#include <nonspliced_aln/nonsplicedAln.hpp>
#include <nonspliced_aln/SeqSAIter.hpp>
#include <nonspliced_aln/StateEntry.hpp>
#include <nonspliced_aln/genmu.hpp>
#include <seqan_api/SeqanAPIUtil.hpp>
#include <seqan_api/SeqSuffixArray_conv.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

void nonsplicedAln(const SeqString& query, std::queue<AlnResult>& result_queue, const SeqSuffixArray& ref_SAIndex, const alnNonspliceOpt& opt)
{
	//Change query and ref_SAIndex back to seqan type
	SeqanSA sa_ref = *conv_back(ref_SAIndex);
	SeqSAIter init_iter(sa_ref);

	//Init start
	StateEntry init_state_entry(init_iter);
	std::queue<StateEntry> se_queue;
	se_queue.emplace(init_state_entry);

	while(!se_queue.empty())
	{
		StateEntry entry = se_queue.front();
		se_queue.pop();
		//If the potential has been found
		if(entry.query_pos == query.get_length())
		{
			//DEBUG
			if(entry.get_seq().get_length() == 0)
			{
				continue;
			}

			AlnResult r;
			r.num_hits = entry.num_hits();
			seqan::Pair<unsigned> sa_range = entry.get_SArange();
			r.SA_index_high = sa_range.i2;
			r.SA_index_low = sa_range.i1;
			r.seq_length = entry.seq_length();
			result_queue.emplace(r);
			//END
		}
		else
		{
			//deal with inseration, deletion, mismatch, and match
			if(entry.state == StateEntry::State::STATE_I)
			{
				if(entry.query_pos != 0)
				{
					produceMatchAndMismatch(entry, se_queue, opt, query[entry.query_pos]);
					produceInsertionFromI(entry, se_queue, opt);
				}
			}
			else if(entry.state == StateEntry::State::STATE_D)
			{
				produceMatchAndMismatch(entry, se_queue, opt, query[entry.query_pos]);
				produceDeletionFromD(entry, se_queue, opt);
			}
			else
			{
				produceMatchAndMismatch(entry, se_queue, opt, query[entry.query_pos]);
				produceInsertionFromM(entry, se_queue, opt);
				produceDeletionFromM(entry, se_queue, opt);
			}
		}
	}
}
