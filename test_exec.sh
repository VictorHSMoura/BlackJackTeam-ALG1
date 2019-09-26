#!/bin/bash
mkdir test_values

echo "5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100" >> test_values/test.csv
for tries in {1..100..1}; do
    line=""
    for teamSize in {5..100..5}; do
        new_line=$(./tp1 dataset/generator_tests/test_$teamSize.txt | tail -1)
        line="$line,$new_line"
    done
    echo $line >> test_values/test.csv
done