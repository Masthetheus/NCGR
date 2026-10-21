#!/bin/bash

DIR="data/results/"
k="12"

for file in "$DIR"*_11_result
do
    [ -e "$file" ] || continue

    short_name=$(basename "$file")

    echo "Processing: $file"
    ./bin/ncgr "$file" "$DIR""$short_name"_cgr
done

echo "All files processed."
