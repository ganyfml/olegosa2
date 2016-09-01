#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

query_file="/Users/gany/test_data/seqs/splicing/seqs.fastq"
ref_file="../../../../../../test_data/index"
./main.exe "$query_file" "$ref_file"
