#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v 

declare -A SpliceType=( [splice_donor]=0 [splice_acceptor]=1)

declare -A Strand=( [none_decide]=0 [forward]=1 [reverse]=2)

splice_type="${SpliceType[splice_donor]}"
splice_strand="${Strand[forward]}"
./main.exe "$splice_type" "$splice_strand"

splice_type="${SpliceType[splice_acceptor]}"
splice_strand="${Strand[forward]}"
./main.exe "$splice_type" "$splice_strand"

splice_type="${SpliceType[splice_donor]}"
splice_strand="${Strand[reverse]}"
./main.exe "$splice_type" "$splice_strand"

splice_type="${SpliceType[splice_acceptor]}"
splice_strand="${Strand[reverse]}"
./main.exe "$splice_type" "$splice_strand"
