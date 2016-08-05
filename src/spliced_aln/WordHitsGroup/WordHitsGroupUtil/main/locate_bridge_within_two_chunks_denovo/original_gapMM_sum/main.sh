#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v 

#        1**  **8
# Ref   TTGTGGAGTT
# Query TA......TT
#        1      2

query=TTTT
ref=TAGTGGAGTT
head_chunk_end_pos_in_ref_and_query=(1 1)
tail_chunk_start_pos_in_ref_and_query=(8 2)
num_backsearch=1

./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"

#              7
#        1 ** **
# Ref   AATGTGAGTT
# Query AA.....TTT
#        1     2

query=AATTT
ref=AATGTGAGTT
head_chunk_end_pos_in_ref_and_query=(1 1)
tail_chunk_start_pos_in_ref_and_query=(7 2)
num_backsearch=1

./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"

#              7
#        1 ** **
# Ref   AAGGTGAGTT
# Query AA.....TTT
#        1     2

query=AATTT
ref=AAGGTGAGTT
head_chunk_end_pos_in_ref_and_query=(1 1)
tail_chunk_start_pos_in_ref_and_query=(7 2)
num_backsearch=1

./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"

#              7
#        1 ** **
# Ref   AATGTGAGTT
# Query AA.....GTT
#        1     2

query=AAGTT
ref=AATGTGAGTT
head_chunk_end_pos_in_ref_and_query=(1 1)
tail_chunk_start_pos_in_ref_and_query=(7 2)
num_backsearch=1

./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"
