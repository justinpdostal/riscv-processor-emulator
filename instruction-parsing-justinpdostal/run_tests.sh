#!/bin/bash

# Directory containing the input files
INPUT_DIR="./tests"

# Directory for output files
OUTPUT_DIR="./output"

# Create the output directory if it doesn't exist
mkdir -p "$OUTPUT_DIR"
i=0

# Iterate through each file in the directory
for file in "$INPUT_DIR"/*; do
  if [[ "$file" == *.archobj ]]; then
    ((i++))
    # Format the index with leading zeros (e.g., 00, 01, etc.)
    formatted_index=$(printf "%02d" $i)
    
    # Create the output filename
    output_file="${OUTPUT_DIR}/${formatted_index}_output.txt"

    echo "Running $file. Writing to $output_file"
    ./r5emu < $file > $output_file
  fi
done
