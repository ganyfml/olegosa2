// vim: set noexpandtab tabstop=3:

#include <../aln_global.hpp>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
  SeqString ref_part((string(argv[1])));
  SeqString query_part((string(argv[2])));
  GapAndMM gap_mm;

  gap_mm.display();
  aln_global(ref_part, query_part, gap_mm);
  gap_mm.display();
}
