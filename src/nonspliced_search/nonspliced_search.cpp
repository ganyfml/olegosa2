// vim: set noexpandtab tabstop=2:

#include <nonspliced_search.hpp>
#define DEBUG

using namespace std;

void produce_insertion(const Ref& ref, const SeqString& query, MutationSet& set, const MutationEntry& entry)
{
	if(entry.get_index() < (get_seqLength(query) - 1))
	{
		for (char char_insert : {'A', 'T', 'C', 'G'})
		{
			MutationEntry toAdd (entry);
			toAdd.seq += char_insert;
			if(toAdd.exist_inRef(ref))
			{
				set.insert(toAdd);
			}
		}
	}
}

void produce_deletion(const Ref& ref, const SeqString& query, MutationSet& set, const MutationEntry& entry)
{
	if(entry.get_index() <= (get_seqLength(query) - 1))
	{
		MutationEntry toAdd (entry);
		if(toAdd.get_index() == (get_seqLength(query) - 1))
		{
			toAdd.increase_index();
			erase_seqBack(toAdd.seq);
		}
		else
		{
			toAdd.increase_index();
			toAdd.seq[get_seqLength(toAdd.seq) - 1] = query[toAdd.get_index()];
		}

		if(toAdd.exist_inRef(ref))
		{
			set.insert(toAdd);
		}
	}
}

void produce_mismatch(const Ref& ref, const SeqString& query, MutationSet& set, const MutationEntry& entry)
{
	for (char char_insert : {'A', 'T', 'C', 'G'})
	{
		MutationEntry toAdd (entry);
		if(char_insert != query[toAdd.get_index() + 1])
		{
			toAdd.seq += char_insert;
			toAdd.increase_index();
			if(toAdd.exist_inRef(ref))
			{
				set.insert(toAdd);
			}
		}
	}
}

MutationPtr produce_mutation(const Ref& ref, const SeqString& query, MutationSet& set, const MutationEntry& entry, regularSearchOpt option)
{
	if(entry.get_state() == MutationState::STATE_M)
	{
		//Insertion
		MutationEntry toInsert (entry);
		++toInsert.gap_mm.num_ref_gapOpen;
		toInsert.change_state(MutationState::STATE_I);
		toInsert.set_score(option.score_mismatch, option.score_gapOpen, option.score_gapExtension);
		if(toInsert.allow_gapOpen(option.max_gapOpen))
		{
			produce_insertion(ref, query, set, toInsert);
		}

		//Deletion
		MutationEntry toDel (entry);
		++toDel.gap_mm.num_query_gapOpen;
		toDel.change_state(MutationState::STATE_D);
		toDel.set_score(option.score_mismatch, option.score_gapOpen, option.score_gapExtension);
		if(toDel.allow_gapOpen(option.max_gapOpen))
		{
			produce_deletion(ref, query, set, toDel);
		}
	}
	else if(entry.get_state() == MutationState::STATE_I)
	{
		//Insertion
		MutationEntry toInsert (entry);
		++toInsert.gap_mm.num_ref_gapExt;
		toInsert.set_score(option.score_mismatch, option.score_gapOpen, option.score_gapExtension);
		if(toInsert.allow_gapExt(option.max_gapExt))
		{
			produce_insertion(ref, query, set, toInsert);
		}
	}
	else if(entry.get_state() == MutationState::STATE_D)
	{
		//Deletion
		MutationEntry toDel (entry);
		++toDel.gap_mm.num_query_gapExt;
		toDel.set_score(option.score_mismatch, option.score_gapOpen, option.score_gapExtension);
		if(toDel.allow_gapExt(option.max_gapExt))
		{
			produce_deletion(ref, query, set, toDel);
		}
	}

	if(entry.get_index() < (get_seqLength(query) - 1))
	{
		MutationEntry toAdd (entry);
		toAdd.change_state(MutationState::STATE_M);
		toAdd.increase_index();
		toAdd.seq += query[toAdd.get_index()];
		if(toAdd.exist_inRef(ref))
		{
			set.insert(toAdd);
		}
		return nullptr;
	}
	else
	{
		return make_shared<MutationEntry>(entry);
	}
}

int aln_nonsplice(const Ref& reference, const SeqString& query, const regularSearchOpt& opt)
{
	MutationSet set;
	MutationSet result_set;
	MutationEntry entry {query[0]};
	set.insert(entry);

	while(set.size())
	{
		MutationEntry top = *(set.begin());
		set.erase(set.begin());
		MutationPtr temp = produce_mutation(reference, query, set, top, opt);
		if(temp != nullptr)
		{
			result_set.insert((*temp));
#ifdef DEBUG
			cout << (*temp).seq << endl;
#endif
		}
	}
	return result_set.size();
}
