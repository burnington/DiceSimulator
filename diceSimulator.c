#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int graph(unsigned int *results, size_t len);
unsigned int pos_ceil(long double num);
void progress_bar(long double complete, long double total);

int main(int argc, char **argv) {
    unsigned int i,
        trials, array_size, *results,
        die1_sides=6, die2_sides=6;

    /* grab args */
    if (argc == 1 || argc > 4) {
        printf("Usage: %s <trials> [die1_sides] [die2_sides]\n", argv[0]);
        return 1;
    }
    switch (argc) {
        case 4:
            die2_sides = atoi(argv[3]);
        case 3:
            die1_sides = atoi(argv[2]);
        case 2:
            trials = atoi(argv[1]);
        default:
            break;
    }

    array_size = die1_sides + die2_sides - 1;

    /* zero out the array */
    results = (unsigned int *) malloc(array_size*sizeof(unsigned int));
    for (i = 0; i < array_size; i++)
        results[i] = 0;

    srand(time(NULL));

    /* simulate dice rolls and sum the results */
    for (i = 0; i < trials; i++) {
        unsigned int dice1, dice2, total;

        dice1 = rand() % die1_sides;
        dice2 = rand() % die1_sides;

        total = dice1 + dice2;
        results[total] += 1;

        progress_bar(i+1, trials);
    }

    /* print out the results */
    for (i = 0; i < array_size; i++)
        printf("%2u: %2u\n", i + 2, results[i]);

    /* graph it in R */
    puts("Graphing results...");
    graph(results, array_size);

    free(results);
    return 0;
}

/**
 * Print out a progress bar.
 * Only updates when it needs to.
 */
void progress_bar(long double complete, long double total) {
    unsigned int i, perc;
    static unsigned int old_perc = 0;

    perc = pos_ceil(100*(complete/total));

    if (perc == old_perc) return;
    old_perc = perc;

    printf("\r%c[2K", 27);
    printf("%u%% ", perc);
    for (i = 0; i < perc/2; i++)
        printf("#");

    if (perc == 100)
        printf("\n");

    fflush(stdout);
}

/**
 * Round up.
 * Only works for pos. numbers.
 */
unsigned int pos_ceil(long double num) {
    int inum = (int)num;

    if (num == (float)inum)
        return inum;

    return ((unsigned int) inum + 1);
}

/**
 * Graph the results using R.
 */
int graph(unsigned int *results, size_t len) {
    FILE *f;
    unsigned int i;

    if (system("which Rscript &>/dev/null") != 0) {
        fprintf(stderr, "error: could not find Rscript\n");
        return -1;
    }

    f = fopen("plot.r", "w");
    fputs(
        "d <- read.csv('data.csv')\n"
        "d$value <- as.numeric(d$value)\n"
        "d$occurrences <- as.numeric(d$occurrences)\n"

        "# uncomment these lines if you want the *percent* occurred\n"
        "# instead of the *total* number occurred (for each value)\n"
        "#sum <- sum(d$occurrences)\n"
        "#d$occurrences <- d$occurrences/sum\n"

        "png('plot.png', width=5, height=5, units='in', res=300)\n"
        "barplot(d$occurrences, names.arg=d$value,\n"
        "        main='Dice Simulator',\n"
        "        xlab='Value (dice1 + dice2)', ylab='Number Occurred')\n"
        "dev.off()\n"
    , f);
    fclose(f);

    f = fopen("data.csv", "w");
    fputs("value,occurrences\n", f);
    for (i = 0; i < len; i++)
        fprintf(f, "%u,%u\n", i+2, results[i]);
    fclose(f);

    system("Rscript ./plot.r &>/dev/null");
    unlink("plot.r");
    unlink("data.csv");

    return 0;
}
