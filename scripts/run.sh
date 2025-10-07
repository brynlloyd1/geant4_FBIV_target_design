#! /bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <detector_setup> <run_name (optional)>"
    exit 1
fi

setup=$1
run_name=$2

rm tmp_files/*.csv

./sim "${setup}" run.mac

if [ -n "$run)name" ]; then
    ./merge_csv.sh "${setup}" "${run_name}"
else
    ./merge_csv.sh "${setup}"
fi

rm tmp_files/*thread*.csv
