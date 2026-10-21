#!/bin/bash

DIR="data/results/"
DIR_OUT="data/results/graphs/"

for file in "$DIR"*_cgr
do
    [ -e "$file" ] || continue

    short_name=$(basename "$file")

    echo "Processing: $file"
    python plot_cgr.py "$file" "$short_name".png
done

echo "All files processed."
