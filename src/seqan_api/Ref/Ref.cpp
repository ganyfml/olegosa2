// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <seqan/find.h>
#include <seqan/index.h>
#include "seqan_api/Ref.hpp"

using namespace std;

typedef seqan::Finder<seqan::Index<seqan::Dna5String, seqan::IndexEsa<>>> T;

bool Ref::loadIndex(const std::string& index_file)
{
	SeqIndex search_index;
	if(!openIndex(search_index, index_file))
	{
		cerr << "Index load failed!" << endl;
		return false;
	}
	else
	{
		search_finder_ = make_shared<SeqFinder>(search_index);
		return true;
	}
}

void Ref::loadIndex(const SeqIndex& index)
{
	search_finder_ = make_shared<SeqFinder>(index);
}

bool Ref::contains(const SeqString& query)
{
	bool ret = search_finder_->find(query);
	search_finder_->clear();
	return ret;
}
