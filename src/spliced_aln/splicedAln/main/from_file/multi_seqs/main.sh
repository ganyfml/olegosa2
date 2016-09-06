#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

#query_file="/Users/gany/test_data/seqs/splicing/error.fasta"
query_file="/Users/gany/test_data/seqs/splicing/error.fasta"
ref_file="/Users/gany/test_data/ref_index/index"
#valgrind --tool=callgrind --collect-atstart=no ./main.exe "$query_file" "$ref_file"
#valgrind --tool=callgrind --collect-atstart=no ./main.exe "$query_file" "$ref_file"
./main.exe "$query_file" "$ref_file"

query_file="/Users/gany/test_data/seqs/splicing/error.fasta"
olego_ref_file="/Users/gany/test_data/mm9_chr1.fa"
/Users/gany/olego/olego "$olego_ref_file" "$query_file"
