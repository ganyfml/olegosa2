#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

#./main_aln.exe "/Users/gany/test_data/query_full.fq" "../../test_data/index"
#./main_aln.exe "/Users/gany/test_data/seqs/query_1000.fq" "../../test_data/index"
#valgrind --tool=callgrind ./main_aln.exe "/Users/gany/test_data/seqs/query_single.fq" "../../test_data/index"
#./main_aln.exe "../../test_data/performance_profiling/query.fq" "../../test_data/performance_profiling/index"
#./main_aln.exe "/Users/gany/test_data/seqs/query_1000.fq" "../../test_data/index"
#valgrind --tool=callgrind --instr-atstart=no ./main_aln.exe "/Users/gany/test_data/seqs/query_1000.fq" "../../test_data/index"
#valgrind --tool=callgrind --instr-atstart=no ./main_aln.exe "/Users/gany/test_data/seqs/query_1000.fq" "../../test_data/index"
#./main_aln.exe "/Users/gany/test_data/seqs/query_100.fq" "../../test_data/index"
#valgrind --tool=callgrind --instr-atstart=no ./main_aln.exe "/Users/gany/test_data/seqs/query_single.fq" "../../test_data/index"
#./main_aln.exe "/Users/gany/test_data/seqs/non-splicing/test_nonsplicing_exact_match_fastq.fq" "/Volumes/ramdisk/index"
#valgrind --tool=callgrind --instr-atstart=no ./main_aln_exact.exe "/Users/gany/test_data/seqs/non-splicing/test_nonsplicing_exact_match_fastq.fq" "/Volumes/ramdisk/index"
#./main_aln_exact.exe "/Users/gany/test_data/seqs/non-splicing/test_nonsplicing_exact_match_fastq.fq" "/Users/gany/test_data/ref_index/index" > exact.result
#./main_aln.exe "/Users/gany/test_data/seqs/non-splicing/test_nonsplicing_exact_match_fastq.fq" "/Users/gany/test_data/ref_index/index" > regular.result
#./main_aln_exact.exe "/tmp/test.fq" "/Users/gany/test_data/ref_index/index" > exact.result
#valgrind --tool=callgrind --instr-atstart=no ./main_aln.exe "/tmp/query_full.fq" "/Users/gany/test_data/ref_index/index"
#~/olego/olego  "/Users/gany/test_data/mm9_chr1.fa" "/tmp/query_full.fq"
./main_exact_aln.exe "/tmp/atest.fastq" "/Users/gany/test_data/ref_index/index"
