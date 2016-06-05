#!/usr/bin/env bash
#vim: set noexpandtab tabstop=2:

#set -v
#query=ATCGATCGATCGATCAGCTA
query=ATCGATC
word_length=2
word_max_overlap=1

function cmd1 {
for((i=0;i<${#query}-1;i+=word_length-word_max_overlap))
do
  #echo $i
  echo "${query:$i:$word_length}"
done
}
function cmd2 {
./main.exe "$word_length" "$word_max_overlap" "$query"
}

diff <(cmd1) <(cmd2)
