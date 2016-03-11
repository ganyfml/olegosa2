// vim: set noexpandtab tabstop=2:
#include "../../Ref.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	SeqString ref_query((string("ATCG")));
	SeqIndex ref_index(ref_query);

	Ref ref(ref_index);
	cout << ref.contains(SeqString(string("A"))) << endl;
}
