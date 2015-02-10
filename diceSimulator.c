#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIE1_NUM_SIDES 6
#define DIE2_NUM_SIDES 6
#define SAMPLE_SIZE    40

#define ARRAY_SIZE DIE1_NUM_SIDES + DIE2_NUM_SIDES - 1

int main(void) {
    int total;
    int combinationArray[ARRAY_SIZE];
    int dice1;
    int dice2;
    int x;
    int y;
    int i;
    
    for (i = 0; i < ARRAY_SIZE; i++) {
        combinationArray[i] = 0;            // Initialize combinationArray[i] to 0
    }

    srand( time(NULL) );

    for (x = 0; x < SAMPLE_SIZE; x++) {
        dice1 = rand() %die1;               // "rolls" the first die
        dice2 = rand() %die2;               // "rolls" the second die
        total = dice1 + dice2;
        combinationArray[total] += 1;       // Increment how many times that number has been rolled
        printf("dice1: %3d\n", dice1);
        printf("dice2: %3d\n", dice2);
        printf("total: %3d\n", total);
        printf("combinationArray[%d]: %d\n\n", total + 2, combinationArray[total]);
    }

    for (y = 0; y < ARRAY_SIZE; y++) {
        printf("combinationArray[%d]:   %d\n", y + 2, combinationArray[y]);         // Print out the array
    }

    /* write CSV data to file */
    FILE *f = fopen("data.csv", "w");
    fputs("value,occurrences\n", f);
    for (i = 0; i < ARRAY_SIZE; i++)
        fprintf(f, "%d,%d\n", i+2, combinationArray[i]);
    fclose(f);

    /* graph it in R */
    system("Rscript ./plot.r &>/dev/null");

    return (0);
}
