#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

word1_refStart=4
word1_colinear=0
word2_refStart=4
word2_colinear=1
./main.exe  "$word1_colinear" "$word1_refStart" "$word2_colinear" "$word2_refStart"

word1_refStart=4
word1_colinear=1
word2_refStart=4
word2_colinear=0
./main.exe  "$word1_colinear" "$word1_refStart" "$word2_colinear" "$word2_refStart"

word1_refStart=3
word1_colinear=1
word2_refStart=4
word2_colinear=1
./main.exe  "$word1_colinear" "$word1_refStart" "$word2_colinear" "$word2_refStart"

word1_refStart=4
word1_colinear=1
word2_refStart=3
word2_colinear=1
./main.exe  "$word1_colinear" "$word1_refStart" "$word2_colinear" "$word2_refStart"
