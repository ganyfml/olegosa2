#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

chunk1_refPosNonDec=1
chunk2_refPosNonDec=0
chunk1_refStart_pos=1
chunk2_refStart_pos=1
./main.exe "$chunk1_refPosNonDec" "$chunk1_refStart_pos" "$chunk2_refPosNonDec" "$chunk2_refStart_pos"

chunk1_refPosNonDec=0
chunk2_refPosNonDec=1
chunk1_refStart_pos=1
chunk2_refStart_pos=1
./main.exe "$chunk1_refPosNonDec" "$chunk1_refStart_pos" "$chunk2_refPosNonDec" "$chunk2_refStart_pos"

chunk1_refPosNonDec=1
chunk2_refPosNonDec=1
chunk1_refStart_pos=1
chunk2_refStart_pos=2
./main.exe "$chunk1_refPosNonDec" "$chunk1_refStart_pos" "$chunk2_refPosNonDec" "$chunk2_refStart_pos"

chunk1_refPosNonDec=1
chunk1_refStart_pos=1
chunk2_refPosNonDec=2
chunk2_refStart_pos=1
./main.exe "$chunk1_refPosNonDec" "$chunk1_refStart_pos" "$chunk2_refPosNonDec" "$chunk2_refStart_pos"

chunk1_refPosNonDec=1
chunk1_refStart_pos=1
chunk2_refPosNonDec=2
chunk2_refStart_pos=2
./main.exe "$chunk1_refPosNonDec" "$chunk1_refStart_pos" "$chunk2_refPosNonDec" "$chunk2_refStart_pos"
