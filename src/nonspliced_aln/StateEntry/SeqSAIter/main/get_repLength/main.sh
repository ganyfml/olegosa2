#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
seq=TCG
godown_char=A
./main.exe "$seq" "$godown_char" 

seq=TCG
godown_char=TA
./main.exe "$seq" "$godown_char" 

seq=ATCG
godown_char=TC
./main.exe "$seq" "$godown_char" 
