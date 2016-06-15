#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

hits_ref_pos=(1 2 3)
./main.exe "${hits_ref_pos[@]}"

hits_ref_pos=(1 202 203)
./main.exe "${hits_ref_pos[@]}"

hits_ref_pos=(1 2 203)
./main.exe "${hits_ref_pos[@]}"

hits_ref_pos=(1 202 403)
./main.exe "${hits_ref_pos[@]}"
