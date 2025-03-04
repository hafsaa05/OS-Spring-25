#!/bin/bash

echo "Enter filename: "
read filename

if [[ -f "$filename" ]]; then
    line_count=$(wc -l < "$filename")
    echo "Number of lines in $filename: $line_count"
else
    echo "File does not exist."
fi
