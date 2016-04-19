// vim: set noexpandtab tabstop=2:

#include <queue>
#include <nonspliced_aln/nonsplicedAln.hpp>
#include <nonspliced_aln/MutationEntry.hpp>
#include <nonspliced_aln/genmu.hpp>
#include <seqan_api/SeqanAPIUtil.hpp>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

void nonsplicedAln(const SeqString& query, const SeqSuffixArray& ref_SAIndex, const alnNonspliceOpt& opt)
{
	//Change query and ref_SAIndex back to seqan type
	SeqanSA sa_ref = *constVoid2localType<SeqanSA>(ref_SAIndex.get_pointer());
	SeqanSAIter init_iter(sa_ref);

	//Init start
	MutationEntry init_mutation_entry(init_iter);
	std::queue<MutationEntry> mutation_queue;
	mutation_queue.emplace(init_mutation_entry);

	while(!mutation_queue.empty())
	{
		MutationEntry entry = mutation_queue.front();
		mutation_queue.pop();
		//If the potential has been found
		if(entry.query_pos == query.get_length())
		{
			//Debug
			using namespace std;
			auto result = entry.get_seq();
			cout << prefix(result, length(result) - entry.extra_step) << endl;
			//End
		}
		else
		{
			//deal with inseration, deletion, mismatch, and match
			if(entry.query_pos != 0)
			{
				produceInsertion(entry, mutation_queue, opt);
			}

			produceDeletion(entry, mutation_queue, opt);

			produceMismatch(entry, mutation_queue, opt, query[entry.query_pos]);

			produceMatch(entry, mutation_queue, opt, query[entry.query_pos]);
		}
	}
}
