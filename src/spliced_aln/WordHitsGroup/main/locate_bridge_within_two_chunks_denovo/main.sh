#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

#        1**  **8
# Ref   TTGTGGAGTT
# Query TT......TT
#        1      2

query=TTTT
ref=TTGTGGAGTT
head_chunk_end_pos_in_ref_and_query=(1 1)
tail_chunk_start_pos_in_ref_and_query=(8 2)
num_backsearch=1

./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"
