#!/bin/bash

# This is a simpler version of the Dice Simulator, similar to the original
# C version you pushed. You know, without all of the extra stuff: argument
# parsing... the progress bar... etc. It should be pretty easy to understand.

# In BASH, constant variables should be all caps.
DIE1_SIDES=6
DIE2_SIDES=6
SAMPLE_SIZE=1000

ARRAY_SIZE=$(($DIE1_SIDES + $DIE2_SIDES - 1))

# Create a new, zero-filled array.
for i in $(seq 1 $ARRAY_SIZE); do
    results[$i]=0
done

# Simulate the dice rolls and sum the results.
for i in $(seq 1 $SAMPLE_SIZE); do
    die1=$(( (RANDOM % DIE1_SIDES) + 1 ))
    die2=$(( (RANDOM % DIE2_SIDES) + 1 ))

    total=$(($die1 + $die2))
    let results[$total]+=1
done

# Overwrite the CSV file.
echo "value,occurrences" > data.csv

# Print out the results, and write it to the CSV.
for i in $(seq 1 $ARRAY_SIZE); do
    let i+=1

    printf "%2d: %2d\n" $i ${results[$i]}
    echo $i,${results[$i]} >> data.csv
done

# Graph it in R.
Rscript ../plot.r &>/dev/null
rm data.csv
