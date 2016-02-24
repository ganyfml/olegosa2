// vim: set noexpandtab tabstop=2:
#include <seqan_api/Ref.hpp>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	//Create SeqString
	std::string ref_seq = argv[1];
  SeqString ref_query(ref_seq);
	SeqStringPtr ref_query_ptr = std::make_shared<SeqString>(ref_query);

	//Create SeqIndex
  SeqIndex ref_index(ref_query);
	createIndex(ref_index);

	//Create Ref
	Ref ref(ref_query_ptr);
	ref.loadIndex(ref_index);

	cout << ref[1] << endl;
}
