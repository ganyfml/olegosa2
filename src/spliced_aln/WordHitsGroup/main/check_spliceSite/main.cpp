// vim: set noexpandtab tabstop=3:

#include<iostream>
#include"../../WordHitsGroup.hpp"

using namespace std;

int main(int, char* argv[])
{
  SeqString ref((string(argv[1])));
  SeqSuffixArray ref_SAIndex(ref);
  int refStart_pos = atoi(argv[2]);
  int refEnd_pos = atoi(argv[3]);
  printf("%d\n", check_spliceSite(ref_SAIndex, refStart_pos, refEnd_pos));
}
