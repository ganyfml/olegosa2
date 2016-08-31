#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

#./main_aln.exe "/Users/gany/test_data/query_full.fq" "../../test_data/index"
#./main_aln.exe "/Users/gany/test_data/seqs/query_1000.fq" "../../test_data/index"
#valgrind --tool=callgrind ./main_aln.exe "/Users/gany/test_data/seqs/query_single.fq" "../../test_data/index"
#./main_aln.exe "../../test_data/performance_profiling/query.fq" "../../test_data/performance_profiling/index"
#./main_aln.exe "/Users/gany/test_data/seqs/query_1000.fq" "../../test_data/index"
#valgrind --tool=callgrind --instr-atstart=no ./main_aln.exe "/Users/gany/test_data/seqs/query_1000.fq" "../../test_data/index"
#valgrind --tool=callgrind --instr-atstart=no ./main_aln.exe "/Users/gany/test_data/seqs/query_1000.fq" "../../test_data/index"
./main_aln.exe "/Users/gany/test_data/seqs/query_100.fq" "../../test_data/index"
