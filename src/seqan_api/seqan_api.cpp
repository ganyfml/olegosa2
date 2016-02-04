// vim: set noexpandtab tabstop=2:

#include <seqan_api.hpp>
#include <seqan/find.h>
#include <seqan/modifier.h>

using namespace std;
using namespace seqan;

Seq::Seq(const string& ref_file, const string& index_file)
{
	ref_file_ = ref_file;
	index_file_ = index_file + "SA_Index";
}

bool Seq::create_SA(int chr_index)
{
	StringSet<CharString> IDSet;
	StringSet<Dna5String> SeqSet;
	SeqFileIn seq_file(toCString(ref_file_));
	readRecords(IDSet, SeqSet, seq_file);
	Index<SeqString, IndexEsa<> > search_index (value(SeqSet, chr_index));

	//FibreSA() may need to be changed to improve performance
	//http://seqan.readthedocs.org/en/master/Tutorial/Indices.html?highlight=fibresa
	if(!indexCreate(search_index, FibreSA()))
	{
		cerr << "Index create failed!" << endl;
		return false;
	}

	if(!save(search_index, toCString(index_file_)))
	{
		cerr << "Index save failed!" << endl;
		return false;
	}

	this->search_index_ = search_index;
	return true;
}

bool Seq::load_SA()
{
	if(!open(this->search_index_, toCString(index_file_)))
	{
		cerr << "Index not exists" << endl;
		return false;
	}
	else
	{
		cout << "Index loading complete" << endl;
	}

	return true;
}

bool Seq::find_exist(const SeqString& target) const
{
	Finder< Index<SeqString, IndexEsa<> > > reference_finder = (search_index_);

	return find(reference_finder, target);
}


SeqString get_reverseComplement(const SeqString& target)
{
	SeqString ret = target;
	reverseComplement(ret);
	return ret;
}

SeqString change_stringInsert(const SeqString& target, int index, char value)
{
	SeqString ret = target;
	insert(ret, index, value);
	return ret;
}

SeqString change_stringRemove(const SeqString& target, int index)
{
	SeqString ret = target;
	erase(ret, index);
	return ret;
}

SeqString get_stringPrefix(const SeqString& target, int index)
{
	return prefix(target, index);
}

SeqString get_stringInfix(const SeqString& target, int start, int end)
{
	return infix(target, start, end);
}

SeqString get_stringSuffix(const SeqString& target, int index)
{
	return suffix(target, index);
}

int get_seqLength(const SeqString& target)
{
	return length(target);
}

void erase_seqBack(SeqString& str)
{
	eraseBack(str);
}
