#!/bin/bash

# Directory containing the students' output files
STUDENT_DIR="tests/solutions"

# Directory containing the example files
EXAMPLES_DIR="tests/examples"

# Iterate through each file in the directory
for file in "$EXAMPLES_DIR"/*.soln; do
  student_file="$STUDENT_DIR/$(basename "$file")"
  
  if [[ ! -f "$student_file" ]]; then
    echo "Missing student output for $(basename "$file")"
    continue
  fi

  diff -w "$file" "$student_file" > /dev/null
  status=$?

  if [[ $status -eq 0 ]]; then
    echo "✅ PASSED: $(basename "$file") matches!"
  elif [[ $status -eq 1 ]]; then
    echo "❌ FAILED: $(basename "$file") differs!"
  else
    echo "⚠️ Error comparing $(basename "$file")"
  fi
done
