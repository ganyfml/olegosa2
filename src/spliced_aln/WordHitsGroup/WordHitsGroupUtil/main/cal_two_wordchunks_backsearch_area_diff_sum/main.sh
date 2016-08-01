#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

ref=TTGG
query=ATGA
head_chunk_end_pos_in_ref_and_query=(1 1)
tail_chunk_start_pos_in_ref_and_query=(2 2)
./main.exe "$ref" "$query" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}"

ref=TTGG
query=TTGA
head_chunk_end_pos_in_ref_and_query=(1 1)
tail_chunk_start_pos_in_ref_and_query=(2 2)
./main.exe "$ref" "$query" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}"

ref=TTGG
query=ATGG
head_chunk_end_pos_in_ref_and_query=(1 1)
tail_chunk_start_pos_in_ref_and_query=(2 2)
./main.exe "$ref" "$query" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}"
