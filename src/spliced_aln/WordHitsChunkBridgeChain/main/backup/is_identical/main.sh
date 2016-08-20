#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

first_bridge_ref_start=0
second_bridge_ref_start=0
first_bridge_ref_end=5
second_bridge_ref_end=5
first_bridge_head_chunk_strand=1
second_bridge_head_chunk_strand=1

./main.exe "$first_bridge_ref_start" "$second_bridge_ref_start" "$first_bridge_ref_end" "$second_bridge_ref_end" "$first_bridge_head_chunk_strand" "$second_bridge_head_chunk_strand"

first_bridge_ref_start=0
second_bridge_ref_start=1
first_bridge_ref_end=5
second_bridge_ref_end=5
first_bridge_head_chunk_strand=1
second_bridge_head_chunk_strand=1
./main.exe "$first_bridge_ref_start" "$second_bridge_ref_start" "$first_bridge_ref_end" "$second_bridge_ref_end" "$first_bridge_head_chunk_strand" "$second_bridge_head_chunk_strand"

first_bridge_ref_start=0
second_bridge_ref_start=0
first_bridge_ref_end=6
second_bridge_ref_end=5
first_bridge_head_chunk_strand=1
second_bridge_head_chunk_strand=1
./main.exe "$first_bridge_ref_start" "$second_bridge_ref_start" "$first_bridge_ref_end" "$second_bridge_ref_end" "$first_bridge_head_chunk_strand" "$second_bridge_head_chunk_strand"

first_bridge_ref_start=0
second_bridge_ref_start=0
first_bridge_ref_end=6
second_bridge_ref_end=5
first_bridge_head_chunk_strand=1
second_bridge_head_chunk_strand=0
./main.exe "$first_bridge_ref_start" "$second_bridge_ref_start" "$first_bridge_ref_end" "$second_bridge_ref_end" "$first_bridge_head_chunk_strand" "$second_bridge_head_chunk_strand"
