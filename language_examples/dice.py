#!/usr/bin/env python3

# This is a simpler version of the Dice Simulator, similar to the original
# C version you pushed. You know, without all of the extra stuff: argument
# parsing... the progress bar... etc. It should be pretty easy to understand.

import os
from random import randrange

# In Python, constant variables should be all caps.
DIE1_SIDES  = 6
DIE2_SIDES  = 6
SAMPLE_SIZE = 1000

ARRAY_SIZE = DIE1_SIDES + DIE2_SIDES - 1

# Create a new, zero-filled array.
results = [0] * ARRAY_SIZE

# Simulate the dice rolls and sum the results.
for i in range(SAMPLE_SIZE):
    die1 = randrange(0, DIE1_SIDES)
    die2 = randrange(0, DIE2_SIDES)

    results[die1 + die2] += 1

# Open the CSV file.
csv = open("data.csv", "w")
csv.write("value,occurrences\n")

# Print out the results, and write it to the CSV.
for i in range(ARRAY_SIZE):
    print("%2d: %2d" % (i+2, results[i]))
    csv.write(str(i+2) + "," + str(results[i]) + "\n")

# Graph it in R.
csv.close()
os.system("Rscript ../plot.r &>/dev/null")
os.remove("data.csv")
