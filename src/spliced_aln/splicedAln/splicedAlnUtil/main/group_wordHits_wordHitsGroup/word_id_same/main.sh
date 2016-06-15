#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

hits_id=(1 2 3)
./main.exe "${hits_id[@]}"

hits_id=(1 2 2)
./main.exe "${hits_id[@]}"

hits_id=(1 1 2)
./main.exe "${hits_id[@]}"

hits_id=(1 1 1)
./main.exe "${hits_id[@]}"
