// vim: set noexpandtab tabstop=2:

#include <queue>
#include <nonspliced_aln/nonsplicedAln.hpp>
#include <nonspliced_aln/SeqSAIter.hpp>
#include <nonspliced_aln/StateEntry.hpp>
#include <nonspliced_aln/genmu.hpp>
#include <seqan_api/SeqanAPIUtil.hpp>
#include <seqan_api/SeqSuffixArray_conv.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

void nonsplicedAln(const SeqString& query, const SeqSuffixArray& ref_SAIndex, const alnNonspliceOpt& opt)
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
			//Debug
			using namespace std;
			auto result = entry.get_seq();
			cout << result << endl;
			//End
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
