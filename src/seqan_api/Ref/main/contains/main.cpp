// vim: set noexpandtab tabstop=2:
#include "seqan_api/Ref.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	std::string ref_seq = argv[1];
  SeqString ref_query(ref_seq);
	SeqStringPtr ref_query_ptr = std::make_shared<SeqString>(ref_query);

  SeqIndex ref_index(ref_query);
	createIndex(ref_index);

	Ref ref(ref_query_ptr);
	ref.loadIndex(ref_index);

	cout << ref.contains((string(argv[2]))) << endl;
}
