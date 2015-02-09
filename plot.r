#!/usr/bin/env Rscript
d <- read.csv("data.csv")
d$value <- as.numeric(d$value)
d$occurrences <- as.numeric(d$occurrences)

# uncomment these lines if you want the *percent* occurred
# instead of the *total* number occurred (for each value)
#sum <- sum(d$occurrences)
#d$occurrences <- d$occurrences/sum

png("plot.png", width=5, height=5, units="in", res=300)
barplot(d$occurrences, names.arg=d$value,
        main="Dice Simulator",
        xlab="Value (dice1 + dice2)", ylab="Number Occurred")
dev.off()
