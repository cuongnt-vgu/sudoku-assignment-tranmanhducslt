#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "setnote.c"
#include "hidden_singles.c"
#include "hidden_pairs.c"
#include "naked_pairs.c"

int nonzeroes(int test[], int L, int R){
    int count = 0;
    for (int i = L; i <= R; ++i)
        if (test[i] != 0) count++;
    return count; // # of array's non-zeroes, from [L] to [R]
}

int compArr(int a[], int b[], int size){
	for (int i = 0; i < size; i++)
		if (a[i] != b[i]) return 0;
	return 1; // comparing two arrays    
}

void load_sudoku(struct cell **pboard, char *textData)
{
    for (int i = 0; i < 9 * 9; i++)
    {
        pboard[i / 9][i % 9].num = textData[i] - '0';
    }
}

int main(int argc, char **argv){
    // second argument is string of 81 chars
    if (argc != 2)
    {
        printf("Usage: %s <sudoku string>\n", argv[0]);
        return 1;
    }

    int solved = 0, stepcount = 0;    
    struct cell **pboard = (struct cell**)malloc(9 * sizeof(int*)); 
    for (int i = 0; i < 9; i++) pboard[i] = board[i];
    
    load_sudoku(pboard, argv[1]);
    setnote(pboard);
    
    // run algorithms
    while (solved < 81)
    {
        // run hidden singles
        stepcount = hidden_singles(pboard);
        if (stepcount){
            printf("hidden_singles %d\n", stepcount);
            continue;
        }
        // run hidden pairs
        stepcount = hidden_pairs(pboard);
        if (stepcount){
            printf("hidden_pairs %d\n", stepcount);
            continue;
        }
        // run naked pairs
        stepcount = naked_pairs(pboard);
        if (stepcount){
            printf("naked_pairs %d\n", stepcount);
            continue;
        }
    }
    
    // return board
    for (int m = 0; m < 81; ++m){
        int i = m / 9, j = m % 9;
        argv[1][m] = pboard[i][j].num + '0';
    }

    free(pboard);
    printf("%s\n", argv[1]);
    return 0;
}