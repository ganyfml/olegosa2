set -v

ref=AGTGTCAGTAGCATG
query=ATTCGTCA
./main.exe "$ref" "$query"

query=AGT
./main.exe "$ref" "$query"
