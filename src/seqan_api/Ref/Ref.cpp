// vim: set noexpandtab tabstop=2:

#include <iostream>
#include <seqan/find.h>
#include <seqan/index.h>
#include <seqan_api/Ref.hpp>

using namespace std;

Ref::Ref(const SeqIndex& index)
	:	search_finder_(SeqFinder(index)) {}

bool Ref::contains(const SeqString& query)
{
	search_finder_.clear();
	return search_finder_.find(query);
}
