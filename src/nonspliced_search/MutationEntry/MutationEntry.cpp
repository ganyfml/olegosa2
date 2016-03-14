// vim: set noexpandtab tabstop=2:

#include <MutationEntry.hpp>

void produce_insertion(const SeqString& original, const Ref& ref, MutationSet& set)
{
	if(query_index_ < (get_seqLength(query) - 1))
	{
		for (char char_insert : {'A', 'T', 'C', 'G'})
		{
			MutationEntry toAdd(this);
			toAdd.seq += char_insert;
			if(toAdd.exist_inRef(ref))
			{
				set.insert(toAdd);
			}
		}
	}
}

void produce_deletion(const SeqString& query, const Ref& ref, MutationSet& set)
{
	if(entry.get_index() <= (get_seqLength(query) - 1))
	{
		MutationEntry toAdd(this);
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

void produce_mismatch(const SeqString& query, const Ref& ref, MutationSet& set)
{
	for (char char_insert : {'A', 'T', 'C', 'G'})
	{
		MutationEntry toAdd (this);
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
