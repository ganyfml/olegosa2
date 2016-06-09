#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

bridge1_head_chunk_index=1
bridge2_head_chunk_index=0
bridge1_tail_chunk_index=1
bridge2_tail_chunk_index=1
bridge1_ref_start=0
bridge2_ref_start=0
bridge1_ref_end=0
bridge2_ref_end=0
./main.exe "$bridge1_head_chunk_index" "$bridge2_head_chunk_index" "$bridge1_tail_chunk_index" "$bridge2_tail_chunk_index" "$bridge1_ref_start" "$bridge2_ref_start" "$bridge1_ref_end" "$bridge2_ref_end"

bridge1_head_chunk_index=0
bridge2_head_chunk_index=0
bridge1_tail_chunk_index=2
bridge2_tail_chunk_index=1
bridge1_ref_start=0
bridge2_ref_start=0
bridge1_ref_end=0
bridge2_ref_end=0
./main.exe "$bridge1_head_chunk_index" "$bridge2_head_chunk_index" "$bridge1_tail_chunk_index" "$bridge2_tail_chunk_index" "$bridge1_ref_start" "$bridge2_ref_start" "$bridge1_ref_end" "$bridge2_ref_end"

bridge1_head_chunk_index=0
bridge2_head_chunk_index=0
bridge1_tail_chunk_index=1
bridge2_tail_chunk_index=1
bridge1_ref_start=1
bridge2_ref_start=0
bridge1_ref_end=0
bridge2_ref_end=0
./main.exe "$bridge1_head_chunk_index" "$bridge2_head_chunk_index" "$bridge1_tail_chunk_index" "$bridge2_tail_chunk_index" "$bridge1_ref_start" "$bridge2_ref_start" "$bridge1_ref_end" "$bridge2_ref_end"

bridge1_head_chunk_index=0
bridge2_head_chunk_index=0
bridge1_tail_chunk_index=1
bridge2_tail_chunk_index=1
bridge1_ref_start=0
bridge2_ref_start=0
bridge1_ref_end=1
bridge2_ref_end=0
./main.exe "$bridge1_head_chunk_index" "$bridge2_head_chunk_index" "$bridge1_tail_chunk_index" "$bridge2_tail_chunk_index" "$bridge1_ref_start" "$bridge2_ref_start" "$bridge1_ref_end" "$bridge2_ref_end"

bridge1_head_chunk_index=0
bridge2_head_chunk_index=0
bridge1_tail_chunk_index=1
bridge2_tail_chunk_index=1
bridge1_ref_start=0
bridge2_ref_start=0
bridge1_ref_end=0
bridge2_ref_end=0
./main.exe "$bridge1_head_chunk_index" "$bridge2_head_chunk_index" "$bridge1_tail_chunk_index" "$bridge2_tail_chunk_index" "$bridge1_ref_start" "$bridge2_ref_start" "$bridge1_ref_end" "$bridge2_ref_end"
