// vim: set noexpandtab tabstop=2:
#include <seqan_api/Ref.hpp>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	//Create SeqString
  SeqString ref_query((string(argv[1])));
	SeqStringPtr ref_query_ptr = std::make_shared<SeqString>(ref_query);

	Ref ref(ref_query_ptr);
	cout << ref[1] << endl;
}