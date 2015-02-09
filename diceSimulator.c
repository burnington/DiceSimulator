#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int total;
    int sampleSize = 40;
    int die1 = 4;
    int die2 = 98;
    int arraySize = die1 + die2 - 1;
    int combinationArray[arraySize];
    int dice1;
    int dice2;
    int x;
    int y;
    int i;
    
    for (i = 0; i < arraySize; i++) {
        combinationArray[i] = 0;
    }

    srand( time(NULL) );

    for (x = 0; x < sampleSize; x++) {
        dice1 = rand() %die1;
        dice2 = rand() %die2;
        total = dice1 + dice2;
        combinationArray[total] += 1;
        printf("dice1: %3d\n", dice1);
        printf("dice2: %3d\n", dice2);
        printf("total: %3d\n", total);
        printf("combinationArray[%d]: %d\n\n", total + 2, combinationArray[total]);
    }

    for (y = 0; y < arraySize; y++) {
        printf("combinationArray[%d]:   %d\n", y + 2, combinationArray[y]);
    }

    return (0);
}
