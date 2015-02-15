#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DIE1_NUM_SIDES 6
#define DIE2_NUM_SIDES 6
#define SAMPLE_SIZE    1000

#define ARRAY_SIZE DIE1_NUM_SIDES + DIE2_NUM_SIDES - 1

int graph(unsigned int *results);
unsigned int pos_ceil(long double num);
void progress_bar(long double complete, long double total);

int main(void) {
    unsigned int i, results[ARRAY_SIZE];

    /* zero out the array */
    for (i = 0; i < ARRAY_SIZE; i++)
        results[i] = 0;

    srand(time(NULL));

    /* simulate dice rolls and sum the results */
    for (i = 0; i < SAMPLE_SIZE; i++) {
        unsigned int dice1, dice2, total;

        dice1 = rand() % DIE1_NUM_SIDES;
        dice2 = rand() % DIE2_NUM_SIDES;

        total = dice1 + dice2;
        results[total] += 1;

        progress_bar(i+1, SAMPLE_SIZE);
    }

    /* print out the results */
    for (i = 0; i < ARRAY_SIZE; i++)
        printf("%2u: %2u\n", i + 2, results[i]);

    /* graph it in R */
    graph(results);

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
int graph(unsigned int *results) {
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
    for (i = 0; i < ARRAY_SIZE; i++)
        fprintf(f, "%u,%u\n", i+2, results[i]);
    fclose(f);

    if (!fork()) {
        system("Rscript ./plot.r &>/dev/null");
        unlink("plot.r");
        unlink("data.csv");
    }

    return 0;
}
