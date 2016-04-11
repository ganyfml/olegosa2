// vim: set noexpandtab tabstop=2:

#include <queue>
#include <nonspliced_aln/nonsplicedAln.hpp>
#include <nonspliced_aln/MutationEntry.hpp>
#include <seqan_api/SeqanAPIUtil.hpp>

//Debug
#include <iostream>
//End

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

void nonsplicedAln(const SeqString& query, const SeqSuffixArray& ref_SAIndex, const alnNonspliceOpt& opt)
{
	//Change query and ref_SAIndex back to seqan type
	SeqanString query_ref = *constVoid2localType<SeqanString>(query.get_pointer());
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
		if(entry.get_ref_pos() == query.get_length())
		{
			//Debug
			using namespace std;
			auto result = entry.get_seq();
			cout << prefix(result, length(result) - entry.get_pos_offset()) << endl;
			//End
		}
		else
		{
			//deal with inseration, deletion, mismatch, and match
			if(entry.get_ref_pos() != 0)
			{
				entry.produceInsertion(mutation_queue, opt);
			}

			entry.produceDeletion(mutation_queue, opt);

			entry.produceMismatch(mutation_queue, opt, query[entry.get_ref_pos()]);

			entry.produceMatch(mutation_queue, opt, query[entry.get_ref_pos()]);
		}
	}
}
