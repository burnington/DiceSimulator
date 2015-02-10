#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIE1_NUM_SIDES 6
#define DIE2_NUM_SIDES 6
#define SAMPLE_SIZE    40

#define ARRAY_SIZE DIE1_NUM_SIDES + DIE2_NUM_SIDES - 1

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

        printf("dice1: %3u\n", dice1);
        printf("dice2: %3u\n", dice2);
        printf("total: %3u\n", total);
        printf("results[%d]: %u\n\n", total + 2, results[total]);
    }

    /* print out the array */
    for (i = 0; i < ARRAY_SIZE; i++)
        printf("results[%u]:   %u\n", i + 2, results[i]);

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
