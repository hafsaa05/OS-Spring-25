#Develop a bash script to automate directory backup tasks. The script should:
#a. Accept a directory path as an argument.
#b. Create a backup of all files in the directory (and its subdirectories) in a specified backup
#directory.
#c. Append the current date to the backup folder's name.
#d. Provide feedback to the user about the backup process, including the number of files and
#directories backed up.

#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <directory_path>"
    exit 1
fi

source_dir=$1
if [ ! -d "$source_dir" ]; then
    echo "Error: Directory not found!"
    exit 1
fi

backup_dir="backup_$(date +%Y-%m-%d_%H-%M-%S)"
mkdir "$backup_dir"

cp -r "$source_dir"/* "$backup_dir"

file_count=$(find "$backup_dir" -type f | wc -l)
dir_count=$(find "$backup_dir" -type d | wc -l)

echo "Backup completed!"
echo "Backup folder: $backup_dir"
echo "Files: $file_count, Directories: $((dir_count - 1))"
