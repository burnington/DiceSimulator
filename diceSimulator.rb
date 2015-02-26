#!/usr/bin/env ruby

# Check that we have between 1 and 4 arguments
if not ARGV.length.between?(1, 4) then
    puts "Usage: #{$0} <trials> [die1_sides] [die2_sides]"
    exit 1
end

# Grab arguments. ('to_i' means "convert to integer")
num_trials = (ARGV[0]).to_i      # no default
die1_sides = (ARGV[1] || 6).to_i # default = 6
die2_sides = (ARGV[2] || 6).to_i # default = 6

# Create a new array full of zeros.
results = Array.new(die1_sides + die2_sides - 1) { 0 }

# Function to draw a progress bar.
def progress_bar(complete, total)
    @old_perc ||= -1
    perc = (100*complete/total).round

    # only update when we get a new percent
    return if perc == @old_perc
    @old_perc = perc

    print "\r#{perc}% #{"#"*(perc/2)}"
    $stdout.flush
end

# Run the trials and collect the data.
num_trials.times do |i|
    die1 = rand(die1_sides)
    die2 = rand(die2_sides)

    results[die1+die2] += 1
    progress_bar(i+1, num_trials)
end
puts ""

# Print out the data to the console and the CSV file.
File.open("data.csv", "w") do |f|
    f.write("value,occurrences\n")

    results.each_with_index do |occurrences, value|
        printf("%2d: %2d\n", value+2, occurrences)
        f.write("#{value+2},#{occurrences}\n");
    end
end

# Graph the data and delete the CSV file.
puts "Graphing results..."
`Rscript ./plot.r`
File.delete("data.csv")
