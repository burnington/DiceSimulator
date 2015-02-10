#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIE1_NUM_SIDES 6
#define DIE2_NUM_SIDES 6
#define SAMPLE_SIZE    1000

#define ARRAY_SIZE DIE1_NUM_SIDES + DIE2_NUM_SIDES - 1

unsigned int pos_ceil(double num);
void progress_bar(double complete, double total);

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

    /* write CSV data to file */
    FILE *f = fopen("data.csv", "w");
    fputs("value,occurrences\n", f);
    for (i = 0; i < ARRAY_SIZE; i++)
        fprintf(f, "%u,%u\n", i+2, results[i]);
    fclose(f);

    /* graph it in R */
    system("Rscript ./plot.r &>/dev/null");

    return 0;
}

/**
 * Print out a progress bar.
 * Only updates when it needs to.
 */
void progress_bar(double complete, double total) {
    unsigned int i, perc;
    static unsigned int old_perc = 0;

    perc = pos_ceil(100*(complete/total));

    if (perc == old_perc) return;
    old_perc = perc;

    printf("\r%u%% ", perc);
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
unsigned int pos_ceil(double num) {
    int inum = (int)num;

    if (num == (float)inum)
        return inum;

    return ((unsigned int) inum + 1);
}
