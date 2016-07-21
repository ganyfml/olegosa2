#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

declare -A chunk1
declare -A chunk2

chunk1=([refPosNonDec]=1 [refStart_pos]=1)
chunk2=([refPosNonDec]=0 [refStart_pos]=1)
./main.exe "${chunk1[refPosNonDec]}" "${chunk1[refStart_pos]}" "${chunk2[refPosNonDec]}" "${chunk2[refStart_pos]}"

chunk1=([refPosNonDec]=0 [refStart_pos]=1)
chunk2=([refPosNonDec]=1 [refStart_pos]=1)
./main.exe "${chunk1[refPosNonDec]}" "${chunk1[refStart_pos]}" "${chunk2[refPosNonDec]}" "${chunk2[refStart_pos]}"

chunk1=([refPosNonDec]=1 [refStart_pos]=1)
chunk2=([refPosNonDec]=1 [refStart_pos]=0)
./main.exe "${chunk1[refPosNonDec]}" "${chunk1[refStart_pos]}" "${chunk2[refPosNonDec]}" "${chunk2[refStart_pos]}"

chunk1=([refPosNonDec]=1 [refStart_pos]=0)
chunk2=([refPosNonDec]=1 [refStart_pos]=1)
./main.exe "${chunk1[refPosNonDec]}" "${chunk1[refStart_pos]}" "${chunk2[refPosNonDec]}" "${chunk2[refStart_pos]}"

chunk1=([refPosNonDec]=1 [refStart_pos]=1)
chunk2=([refPosNonDec]=1 [refStart_pos]=1)
./main.exe "${chunk1[refPosNonDec]}" "${chunk1[refStart_pos]}" "${chunk2[refPosNonDec]}" "${chunk2[refStart_pos]}"
