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

	ref.find((string(argv[2])));
	cout << ref.location() << endl;
}
