#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v 

declare -A SpliceType=( [splice_donor]=0 [splice_acceptor]=1)

declare -A Strand=( [none_decide]=0 [forward]=1 [reverse]=2)

ref=GT
ref_pos=0
splice_type="${SpliceType[splice_donor]}"
splice_strand="${Strand[forward]}"
./main.exe "$ref" "$ref_pos" "$splice_type" "$splice_strand"

ref=GG
ref_pos=0
splice_type="${SpliceType[splice_donor]}"
splice_strand="${Strand[forward]}"
./main.exe "$ref" "$ref_pos" "$splice_type" "$splice_strand"

ref=CT
ref_pos=1
splice_type="${SpliceType[splice_donor]}"
splice_strand="${Strand[reverse]}"
./main.exe "$ref" "$ref_pos" "$splice_type" "$splice_strand"

ref=CC
ref_pos=1
splice_type="${SpliceType[splice_donor]}"
splice_strand="${Strand[reverse]}"
./main.exe "$ref" "$ref_pos" "$splice_type" "$splice_strand"

ref=AG
ref_pos=1
splice_type="${SpliceType[splice_acceptor]}"
splice_strand="${Strand[forward]}"
./main.exe "$ref" "$ref_pos" "$splice_type" "$splice_strand"

ref=GG
ref_pos=1
splice_type="${SpliceType[splice_acceptor]}"
splice_strand="${Strand[forward]}"
./main.exe "$ref" "$ref_pos" "$splice_type" "$splice_strand"

ref=AC
ref_pos=0
splice_type="${SpliceType[splice_acceptor]}"
splice_strand="${Strand[reverse]}"
./main.exe "$ref" "$ref_pos" "$splice_type" "$splice_strand"

ref=AA
ref_pos=0
splice_type="${SpliceType[splice_acceptor]}"
splice_strand="${Strand[reverse]}"
./main.exe "$ref" "$ref_pos" "$splice_type" "$splice_strand"
