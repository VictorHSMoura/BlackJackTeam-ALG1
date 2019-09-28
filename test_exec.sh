#!/bin/bash
if [ -d dataset/generator_tests ]; then
    rm -r dataset/generator_tests
fi

if [ -d test_values ]; then
    rm -r test_values
fi

cd dataset
python generator.py
cd ..

mkdir test_values

echo "5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100" >> test_values/test.csv
for tries in {1..100..1}; do
    line=""
    for teamSize in {100..5..-5}; do
        new_line=$(./tp1 dataset/generator_tests/test_$teamSize.txt 'time' | tail -1)
        line="$new_line,$line"
    done
    echo ${line::-1} >> test_values/test.csv
done