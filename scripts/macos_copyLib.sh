#!/bin/bash

# Define the source and destination directories
sourceDir="../libraries"
destDir="$HOME/Documents/Arduino/libraries"

# Check if source directory exists
if [ ! -d "$sourceDir" ]; then
    echo "Source directory does not exist"
    exit 1
fi

# Check if destination directory exists
if [ ! -d "$destDir" ]; then
    echo "Destination directory does not exist"
    exit 1
fi

# Copy files and directoris
cp -R "$sourceDir"/* "$destDir"

echo "Subdirectories and files copied successfully"