// vim: set noexpandtab tabstop=2:
#include "../../Ref.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	SeqString ref_query((string(argv[1])));
	SeqIndex ref_index(ref_query);

	SeqStringPtr ref_query_ptr = std::make_shared<SeqString>(ref_query);
	Ref ref(ref_query_ptr);
	ref.loadIndex(ref_index);

	std::string query_seq = argv[2];
	while(ref.find(string(argv[2])))
	{
		cout << ref.position() << endl;
	}
}
