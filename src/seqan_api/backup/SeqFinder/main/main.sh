#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -x
ref=AGATGTCAGATAGCATG
query=AT
./main.exe "$ref" "$query"
