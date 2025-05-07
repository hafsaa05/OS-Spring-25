#Write a Shell Bash Script for evaluate the status of a file/directory.

#!/bin/bash

echo "Enter the file or directory name:"
read input_name  

if [ -f "$input_name" ]; then
    echo "$input_name is a file."
elif [ -d "$input_name" ]; then
    echo "$input_name is a directory."
else
    echo "$input_name does not exist."
fi
