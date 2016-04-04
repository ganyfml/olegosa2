// vim: set noexpandtab tabstop=2:

#include <queue>
#include <nonspliced_aln/nonsplicedAln.hpp>
#include <nonspliced_aln/MutationEntry.hpp>

#include <iostream>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> SeqanSA;
typedef seqan::Iterator<SeqanSA, seqan::TopDown<seqan::ParentLinks<>>>::Type SeqanSAIter;

void nonsplicedAln(const SeqString& query, const SeqSuffixArray& ref_SAIndex, const alnNonspliceOpt& opt)
{
	//Change query and ref_SAIndex back to seqan type
	SeqanString query_ref = static_cast<SeqanString*>(const_cast<void*>(query_ref.get_pointer()));
	SeqanSAIter init_iter(ref_SAIndex);
	MutationEntry init_mutation_entry(init_iter);

	//Init start
	std::queue<MutationEntry> mutation_queue;
	mutation_queue.emplace(init_mutation_entry);

	while(!mutation_queue.empty())
	{
		MutationEntry entry = mutation_queue.front();
		mutation_queue.pop();
		//If the potential has been found
		if(entry.get_ref_pos() == query.get_length())
		{
			printf("Result found");
			std::cout << entry.get_seq() << endl;
		}
		else
		{
			//deal with inseration, deletion, mismatch, and match
			if(entry.get_ref_pos() != 0)
			{
				produceInsertion(mutation_queue, opt);
			}

			produceDeletion(mutation_queue, opt);

			produceMismatch(mutation_queue, opt, queue[entry.get_ref_pos()]);

			produceMatch(mutation_queue, opt, queue[entry.get_ref_pos()]);
		}
	}
}
