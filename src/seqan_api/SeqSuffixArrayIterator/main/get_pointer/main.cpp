// vim: set noexpandtab tabstop=2:
#include "../../SeqSuffixArrayIterator.hpp"
#include "seqan_api/SeqanAPIUtil.hpp"
#include <seqan/index.h>
#include <seqan/seq_io.h>

typedef seqan::Dna5String SeqanString;
typedef seqan::Index<SeqanString, seqan::IndexEsa<>> T;

using namespace std;

int main(int argc, char* argv[])
{
	SeqSuffixArray ref_sa(SeqString(string("ACG")));
	SeqSuffixArrayIterator ref_SA(ref_sa);
	constVoid2localType<T>(ref_SA.get_pointer());
}
