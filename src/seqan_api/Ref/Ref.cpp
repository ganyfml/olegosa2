// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <seqan/find.h>
#include <seqan/index.h>
#include <seqan_api/Ref.hpp>

using namespace std;

typedef seqan::Finder<seqan::Index<seqan::Dna5String, seqan::IndexEsa<>>> T;

bool Ref::load_SAFinder(const std::string& index_file)
{
	SeqIndex search_index;
	if(!openIndex(search_index, index_file))
	{
		cerr << "Index load failed!" << endl;
		return false;
	}
	else
	{
		cout << "Index loading complete" << endl;
		search_finder_ = make_shared<SeqFinder>(SeqFinder(search_index));
		return true;
	}
}

bool Ref::contains(const SeqString& query)
{
	search_finder_->clear();
	bool ret = search_finder_->find(query);
	search_finder_->clear();
	return ret;
}

inline bool Ref::find(const SeqString& seq)
{
	return search_finder_->find(seq);
}

inline unsigned long Ref::location()
{
	return search_finder_->location();
}

inline void Ref::reset_finder()
{
	search_finder_->clear();
}
