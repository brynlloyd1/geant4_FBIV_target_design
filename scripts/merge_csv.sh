#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <detector_setup>"
    exit 1
fi

setup="$1"

cd tmp_files
# should create target_design/data folder
OUTPUT_DIR="../../../data/${setup}"
mkdir -p "${OUTPUT_DIR}"

TIMESTAMP=$(date +%s)

FINAL_OUTPUT="${OUTPUT_DIR}/beam_data_${setup}_${TIMESTAMP}.csv"

# Get the header from the first file
firstFile=$(ls beam_data_thread*.csv | head -n 1)
head -n 1 "$firstFile" >>"$FINAL_OUTPUT"

# Append all data (skip headers)
for file in beam_data_thread*.csv; do
    tail -n +2 "$file" >>"$FINAL_OUTPUT"
done

cd - >/dev/null
echo "Merged files into ${FINAL_OUTPUT}"
