#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

chunk1_colinearity=0
chunk1_refStart_pos=1
chunk2_colinearity=2
chunk2_refStart_pos=2
./main.exe "$chunk1_colinearity" "$chunk1_refStart_pos" "$chunk2_colinearity" "$chunk2_refStart_pos"

chunk1_colinearity=1
chunk1_refStart_pos=0
chunk2_colinearity=2
chunk2_refStart_pos=2
./main.exe "$chunk1_colinearity" "$chunk1_refStart_pos" "$chunk2_colinearity" "$chunk2_refStart_pos"

chunk1_colinearity=1
chunk1_refStart_pos=1
chunk2_colinearity=1
chunk2_refStart_pos=2
./main.exe "$chunk1_colinearity" "$chunk1_refStart_pos" "$chunk2_colinearity" "$chunk2_refStart_pos"

chunk1_colinearity=1
chunk1_refStart_pos=1
chunk2_colinearity=2
chunk2_refStart_pos=1
./main.exe "$chunk1_colinearity" "$chunk1_refStart_pos" "$chunk2_colinearity" "$chunk2_refStart_pos"

chunk1_colinearity=1
chunk1_refStart_pos=1
chunk2_colinearity=2
chunk2_refStart_pos=2
./main.exe "$chunk1_colinearity" "$chunk1_refStart_pos" "$chunk2_colinearity" "$chunk2_refStart_pos"
