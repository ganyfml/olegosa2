// vim: set noexpandtab tabstop=2:

#include <util/GapAndMM.hpp>
#include <nonspliced_aln.hpp>
#include <seqan/index.h>
#include <seqan/seq_io.h>
#include <queue>

using namespace seqan;

typedef Dna5String SeqanString;
typedef Index<SeqanString, IndexEsa<>> SeqanSA;
typedef Iterator<SeqanSA, TopDown<ParentLinks<>>>::Type SeqanSAIter;

class MutationEntry
{
	SeqanSAIter ref_iter;
	unsigned long ref_pos;
	int score;
	GapAndMM gap_mm;
	enum state;

	MutationEntry(const SeqanSAIter& init_iter)
		: ref_pos(0), ref_iter(init_iter), score(0) {}

	MutationEntry(const MutationEntry& that)
		: ref_pos(that.ref_pos), ref_iter(that.ref_iter), gap_mm(that.gap_mm), score(that.score) {}

	void produceInsertion(std::queue<MutationEntry>& mutation_queue)
	{
		for(char char_insert : {'A', 'T', 'C', 'G'})
		{
			if(goDown(ref_iter, char_insert))
			{
				MutationEntry insert_one;
				insert_one.ref_iter = ref_iter;
				insert_one.ref_pos = ref_pos;
				insert_one.gap_mm = gap_mm;
				if(state == STATE_M)
				{

				}else
				{

				}
				mutation_queue.emplace(insert_one);
				goUp(base_sa_iter);
			}
		}
	}
};

void aln_nonsplice(const SeqSuffixArray& reference, const SeqString& query, const aln_nonspliceOpt& opt)
{
	SeqanSA ref_SA = *static_cast<SeqanSA*>(const_cast<void*>(reference.get_pointer()));
	SeqanSAIter ref_iter(ref_SA);
	std::queue<MutationEntry> mutation_queue;

	MutationEntry first;
	goDown(ref_iter, rawtextAt(0, ref_SA));
	first.ref_iter = ref_iter;
	first.ref_pos = 0;
	first.score = 0;
	mutation_queue.emplace(first);

	while(mutation_queue.size != 0)
	{
		MutationEntry base = mutation_queue.pop();
		unsigned long base_ref_pos = base.ref_pos;
		SeqanSAIter base_sa_iter = base.ref_iter;

		//Inseration
		//Deletion
		if(goDown(base_sa_iter, rawtextAt(base.ref_pos + 1, base_sa_iter)))
		{
			MutationEntry delete_one;
			delete_one.ref_iter = base_sa_iter;
			delete_one.ref_pos = base.ref_pos + 2;
			delete_one.gap_mm = base.gap_mm;
			mutation_queue.emplace(delete_one);
			goUp(base_sa_iter);
		}

		//Excat match and Mismatch
		for(char char_insert : {'A', 'T', 'C', 'G'})
		{
			if(char_insert != rawtextAt(base.ref_pos + 1, base_sa_iter) && mismatch_allowed)
			{
				if(goDown(base_sa_iter, char_insert))
				{
					MutationEntry insert_one;
					insert_one.ref_iter = base_sa_iter;
					insert_one.ref_pos = base.ref_pos + 1;
					insert_one.gap_mm = base.gap_mm;
					mutation_queue.emplace(insert_one);
					goUp(base_sa_iter);
				}
			}
		}

		if(goDown(base_sa_iter, rawtextAt(base.ref_pos + 1, base_sa_iter)))
		{
			MutationEntry exact;
			exact.ref_iter = base_sa_iter;
			exact.ref_pos = base.ref_pos + 1;
			exact.gap_mm = base.gap_mm;
			goUp(base_sa_iter);
		}
	}
}
