#!/bin/bash

echo "Enter a sentence:"
read sentence  

vowels=0  

for (( i=0; i<${#sentence}; i++ )); do
    char=${sentence:$i:1}  
    case "$char" in
        [aeiouAEIOU]) ((vowels++)) ;;  
    esac
done

echo "Number of vowels: $vowels"  
