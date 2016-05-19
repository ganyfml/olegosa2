#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -x
ref=AAATACAG
exist_part=A
next_char=C

./main.exe "$ref" "$exist_part" "$next_char"

./main1.exe "$ref" "$exist_part" "$next_char"
