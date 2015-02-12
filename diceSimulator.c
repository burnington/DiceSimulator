#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int die1 = 6;                           // Amount of sides on the first die
    int die2 = 6;                           // Amount of sides on the second die
    int sampleSize = 40;                    // Number of "rolls"

    int total;
    int arraySize = die1 + die2 - 1;        // calculates the needed amount of elements for the array
    int combinationArray[arraySize];
    int dice1;
    int dice2;
    int x;
    int y;
    int i;
    
    for (i = 0; i < arraySize; i++) {
        combinationArray[i] = 0;            // Initialize combinationArray[i] to 0
    }

    srand( time(NULL) );

    for (x = 0; x < sampleSize; x++) {
        dice1 = rand() %die1;               // "rolls" the first die
        dice2 = rand() %die2;               // "rolls" the second die
        total = dice1 + dice2;
        combinationArray[total] += 1;       // Increment how many times that number has been rolled
        printf("dice1: %3d\n", dice1);
        printf("dice2: %3d\n", dice2);
        printf("total: %3d\n", total);
        printf("combinationArray[%d]: %d\n\n", total + 2, combinationArray[total]);
    }

    for (y = 0; y < arraySize; y++) {
        printf("combinationArray[%d]:   %d\n", y + 2, combinationArray[y]);         // Print out the array
    }

    /* write CSV data to file */
    FILE *f = fopen("data.csv", "w");
    fputs("value,occurrences\n", f);
    for (i = 0; i < arraySize; i++)
        fprintf(f, "%d,%d\n", i+2, combinationArray[i]);
    fclose(f);

    /* graph it in R */
    system("Rscript ./plot.r &>/dev/null");
    unlink("data.csv");

    return (0);
}
