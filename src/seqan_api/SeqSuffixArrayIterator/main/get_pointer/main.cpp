// vim: set noexpandtab tabstop=2:
#include "../../SeqSuffixArrayIterator.hpp"
#include "../../../SeqanAPIUtil/SeqanAPIUtil.hpp"
#include <seqan/index.h>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> T;

using namespace std;

int main(int argc, char* argv[])
{
	SeqString seq(string("ACG"));
	SeqSuffixArray ref_sa(seq);

	SeqSuffixArrayIterator ref_SA_iter(ref_sa);
	constVoid2localType<T>(ref_SA_iter.get_pointer());
}
