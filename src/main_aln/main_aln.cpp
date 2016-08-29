// vim: set noexpandtab tabstop=3:

//Debug
#include <valgrind/callgrind.h>
//End
#include <nonspliced_aln/nonsplicedAln.hpp>
#include <seqan_api/SeqStringSet.hpp>
#include <seqan_api/CharStringSet.hpp>
#include <util/OutputWriter.hpp>

int main(int, char* argv[])
{
  std::string query_in(argv[1]);

  SeqStringSet querys;
  CharStringSet ids;
  CharStringSet quals;
  load_seqs_with_qual(query_in, querys, ids, quals);

  std::string ref_in(argv[2]);
  SeqSuffixArray ref_SAIndex(ref_in);
  alnNonspliceOpt opt;
  opt.max_gapOpen = 2;
  opt.max_gapExt = 2;
  std::cout << "loading complete" << std::endl;

  SAMWritter sam_file;
  CALLGRIND_START_INSTRUMENTATION;

  //Debug
#include <ctime>
  std::clock_t    start;
  start = std::clock();
  //End

  for(int i = 0; i < querys.get_length(); ++i)
  {
	 SeqString query = querys[i];
	 std::list<AlnResult> result_list;
	 nonsplicedAln(query, result_list, ref_SAIndex, opt);
	 printf("%ld\n", result_list.size());
	 //if(!result_list.empty())
	 //{
	 //  std::cout << result_list.size() << std::endl;
	 //  while(!result_list.empty())
	 //  {
	 //    AlnResult result = result_list.front();
	 //    result_list.pop_front();
	 //    for(unsigned long position = result.SA_index_low; position < result.SA_index_high; ++position)
	 //    {
	 //  	 sam_file.write_record(query, position, result.seq_length, ref_SAIndex, ids[i], quals[i]);
	 //    }
	 //  }
	 //}
	 //else
	 //{
	 //  sam_file.write_record_with_no_hit(query, ids[i], quals[i]);
	 //}
  }
  //Debug
  std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
  //End
  CALLGRIND_STOP_INSTRUMENTATION;
  CALLGRIND_DUMP_STATS;
}
