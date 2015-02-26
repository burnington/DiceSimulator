#!/usr/bin/env ruby

# This is a simpler version of the Dice Simulator, similar to the original
# C version you pushed. You know, without all of the extra stuff: argument
# parsing... the progress bar... etc. It should be pretty easy to understand.

# In Ruby, constant variables should be all caps.
DIE1_SIDES = 6
DIE2_SIDES = 6
SAMPLE_SIZE    = 1000

ARRAY_SIZE = DIE1_SIDES + DIE2_SIDES - 1

# Create a new, zero-filled array.
results = Array.new(ARRAY_SIZE) {0}

# Simulate the dice rolls and sum the results.
SAMPLE_SIZE.times do |i|
    die1 = rand(DIE1_SIDES)
    die2 = rand(DIE2_SIDES)

    total = die1 + die2
    results[die1 + die2] += 1
end

# Open the CSV file.
csv = File.open("data.csv", "w")
csv.write("value,occurrences\n")

# Print out the results, and write it to the CSV.
results.each_with_index do |occurrences, value|
    printf("%2d: %2d\n", value+2, occurrences)
    csv.write("#{value+2},#{occurrences}\n")
end

# Graph it in R.
csv.close
`Rscript ./plot.r`
File.delete("data.csv")
