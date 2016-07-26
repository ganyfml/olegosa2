#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

head_chunk_end_pos_in_ref_and_query=(1 1)
tail_chunk_start_pos_in_ref_and_query=(8 2)
ref=TTGTGGAGTT
query=TTTT
num_backsearch=1

./main.exe "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch" "$query" "$ref"
