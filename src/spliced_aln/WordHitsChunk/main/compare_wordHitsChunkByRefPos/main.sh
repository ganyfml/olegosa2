#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

declare -A chunk1
declare -A chunk2

chunk1=([refPosNonDec]=1 [start_pos_in_ref]=1)
chunk2=([refPosNonDec]=0 [start_pos_in_ref]=1)
./main.exe "${chunk1[refPosNonDec]}" "${chunk1[start_pos_in_ref]}" "${chunk2[refPosNonDec]}" "${chunk2[start_pos_in_ref]}"

chunk1=([refPosNonDec]=0 [start_pos_in_ref]=1)
chunk2=([refPosNonDec]=1 [start_pos_in_ref]=1)
./main.exe "${chunk1[refPosNonDec]}" "${chunk1[start_pos_in_ref]}" "${chunk2[refPosNonDec]}" "${chunk2[start_pos_in_ref]}"

chunk1=([refPosNonDec]=1 [start_pos_in_ref]=1)
chunk2=([refPosNonDec]=1 [start_pos_in_ref]=0)
./main.exe "${chunk1[refPosNonDec]}" "${chunk1[start_pos_in_ref]}" "${chunk2[refPosNonDec]}" "${chunk2[start_pos_in_ref]}"

chunk1=([refPosNonDec]=1 [start_pos_in_ref]=0)
chunk2=([refPosNonDec]=1 [start_pos_in_ref]=1)
./main.exe "${chunk1[refPosNonDec]}" "${chunk1[start_pos_in_ref]}" "${chunk2[refPosNonDec]}" "${chunk2[start_pos_in_ref]}"

chunk1=([refPosNonDec]=1 [start_pos_in_ref]=1)
chunk2=([refPosNonDec]=1 [start_pos_in_ref]=1)
./main.exe "${chunk1[refPosNonDec]}" "${chunk1[start_pos_in_ref]}" "${chunk2[refPosNonDec]}" "${chunk2[start_pos_in_ref]}"
