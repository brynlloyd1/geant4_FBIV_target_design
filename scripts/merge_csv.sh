#!/bin/bash

# Output file
output="beam_data.csv"

# Start fresh
rm -f $output

# Get the header from the first file
firstFile=$(ls beam_data_thread*.csv | head -n 1)
head -n 1 "$firstFile" >$output

# Append all data (skip headers)
for file in beam_data_thread*.csv; do
    tail -n +2 "$file" >>$output
done

echo "✅ Merged files into $output"
