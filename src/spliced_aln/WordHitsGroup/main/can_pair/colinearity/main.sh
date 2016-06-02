#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

set -v

head_colinear=1
tail_colinear=0
./main.exe "$head_colinear" "$tail_colinear"

head_colinear=0
tail_colinear=1
./main.exe "$head_colinear" "$tail_colinear"

head_colinear=0
tail_colinear=0
./main.exe "$head_colinear" "$tail_colinear"

head_colinear=1
tail_colinear=1
./main.exe "$head_colinear" "$tail_colinear"
