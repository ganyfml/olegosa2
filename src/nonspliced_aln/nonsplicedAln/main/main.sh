#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v
ref=ATGTACTACGATATGTCTAGCTACGACTGACACGATCAGCT
query=ATGCA
./main.exe "$ref" "$query"
