#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v 

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

#         2 **  **10
# Ref   TTTAGTGGAGTTT
# Query TTTA......TTT
#         2      4

query=TTTATTT
ref=TTTAGTGGAGTTT
head_chunk_end_pos_in_ref_and_query=(2 2)
tail_chunk_start_pos_in_ref_and_query=(10 4)
num_backsearch=1

./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"

#         2 **  **10
# Ref   TTTGTGGAGATTT
# Query TTT......ATTT
#         2      4

query=TTTATTT
ref=TTTGTGGAGATTT
head_chunk_end_pos_in_ref_and_query=(2 2)
tail_chunk_start_pos_in_ref_and_query=(10 4)
num_backsearch=1

./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"

#         2
#         **  ** 9
# Ref   TTGTGGAGTAA
# Query TTT......AA
#         2      3

query=TTTTT
ref=TTGTGGAGTTT
head_chunk_end_pos_in_ref_and_query=(2 2)
tail_chunk_start_pos_in_ref_and_query=(9 3)
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
