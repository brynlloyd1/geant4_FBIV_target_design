#! /bin/zsh

rm tmp_files/*.csv

./sim run.mac

cd tmp_files
./merge_csv.sh cd ..
