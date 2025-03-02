#!/bin/bash

echo "Enter the filename:"
read filename  

if [ -f "$filename" ]; then
    echo "$(date)" >> "$filename"
    echo "Date and time appended to $filename"
else
    echo "File does not exist."
fi
