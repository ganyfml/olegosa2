// vim: set noexpandtab tabstop=2:

#include <internal_dir.mk.hpp>
#define DEBUG

using namespace std;

void produce_insertion(const Seq& ref, const SeqString& query, MutationSet& set, const MutationEntry& entry)
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

void produce_deletion(const Seq& ref, const SeqString& query, MutationSet& set, const MutationEntry& entry)
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

void produce_mismatch(const Seq& ref, const SeqString& query, MutationSet& set, const MutationEntry& entry)
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

