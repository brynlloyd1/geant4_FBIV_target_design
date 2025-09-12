#! /bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <detector_setup>"
    exit 1
fi

setup=$1

rm tmp_files/*.csv

./sim "${setup}" run.mac

./merge_csv.sh "${setup}"

rm tmp_files/*thread*.csv
