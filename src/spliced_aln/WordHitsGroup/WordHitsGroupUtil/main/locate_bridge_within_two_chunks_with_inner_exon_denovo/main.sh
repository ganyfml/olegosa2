#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v 

#                       16
#        1**  **  **  **|
# Ref   TTGTGGAGAAGTGGAGTT
# Query TT......AA......TT
#        1              4
#
#                       16
#        1**  **89**  **|
# Ref   TTGTGGAGAAGTGGAGTT
# Query TT......AA......TT
#        1      23      4

query=TTAATT
ref=TTGTGGAGAAGTGGAGTT
head_chunk_end_pos_in_ref_and_query=(1 1)
tail_chunk_start_pos_in_ref_and_query=(16 4)
num_backsearch=1
./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"

#          3           16
#         **  **89**  **|
# Ref   TTGTGGAGAAGTGGAGTTT
# Query TTAA............TTT
#          3            4
#
#                      16
#        1**  **89**  **|
# Ref   TTGTGGAGAAGTGGAGTTT
# Query TT......AA......TTT
#        1      23      4

query=TTAATTT
ref=TTGTGGAGAAGTGGAGTTT
head_chunk_end_pos_in_ref_and_query=(3 3)
tail_chunk_start_pos_in_ref_and_query=(16 4)
num_backsearch=2
./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"

#                10   15
#         2**  **9|**  **|
# Ref   TTTGTGGAGAAGTGGAGTTT
# Query TTT............AATTT
#         2            3
#
#                10     17
#         2**  **9|**  **|
# Ref   TTTGTGGAGAAGTGGAGTTT
# Query TTT......AA......TTT
#         2      34      5

query=TTTAATTT
ref=TTTGTGGAGAAGTGGAGTTT
head_chunk_end_pos_in_ref_and_query=(2 2)
tail_chunk_start_pos_in_ref_and_query=(15 3)
num_backsearch=2
./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"

#                        16
#          3     10      /
#          **  **9|**  **
# Ref   TTTGTGGAGAAGTGGAGTTT
# Query TTTA............ATTT
#          3            4
#
#                10     17
#         2**  **9|**  **|
# Ref   TTTGTGGAGAAGTGGAGTTT
# Query TTT......AA......TTT
#         2      34      5

query=TTTAATTT
ref=TTTGTGGAGAAGTGGAGTTT
head_chunk_end_pos_in_ref_and_query=(3 3)
tail_chunk_start_pos_in_ref_and_query=(16 4)
num_backsearch=2
./main.exe "$query" "$ref" "${head_chunk_end_pos_in_ref_and_query[@]}" "${tail_chunk_start_pos_in_ref_and_query[@]}" "$num_backsearch"
