// vim: set noexpandtab tabstop=2:
#include "../SeqSuffixArrayIterator.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	SeqSuffixArray ref_sa(SeqString(string("ACG")));

	SeqSuffixArrayIterator ref_sa_iter(ref_sa);
}
