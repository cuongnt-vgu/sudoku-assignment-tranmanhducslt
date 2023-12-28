#include <stdio.h>
#include <stdlib.h>
#include "hidden_singles.c"
#include "hidden_pairs.c"
#include "naked_pairs.c"

int nonzeroes(int test[], int M, int N){
    int count = 0;
    for (int i = M; i < N; ++i)
        if (test[i] != 0) count++;
    return count; // # of array's non-zeroes, from [M] to [N - 1]
}

int compArr(int a[], int b[], int size){
	for (int i = 0; i < size; i++)
		if (a[i] != b[i]) return 0;
	return 1; // comparing two arrays
}

void torevbin(char n, int *s){
    // number to reversed binary
    int m = 0, i = 0;
    while (map[m] != n) m++;
    while (m > 0){
        s[i] = (m % 2);
        i++; m /= 2;
    }
}

char tochar(int *s){
    // reversed binary to number
    int n = 0, p = 1;
    for (int i = 0; i < 5; i++) {
        n += s[i] * p;
        p *= 2;
    }
    return map[n];
}

int main(){
    FILE *fptr;
        fptr = fopen("sudokustr.txt", "r");
	if (fptr == NULL){
		printf("Cannot find file\n");
		return 1;
	}
    // string to board layout
    char myStr[163]; // must add 1 for the '\0'
    fgets(myStr, 163, fptr);
	for (int m = 0; m < 81; ++m){
	    int i = m / 9, j = m % 9;
		int ctr = 2 * (9 * i + j);
        torevbin(myStr[ctr], (board[i][j].cand + 5));
        torevbin(myStr[ctr + 1], board[i][j].cand);
        if (board[i][j].cand[0] == 1)
            for (int k = 1; k < 10; ++k)
                if (board[i][j].cand[k] == 1){
                    board[i][j].num = k;
                    break;
                }
    }

    // pointer to board, to directly modify board
    struct cell **pboard = (struct cell**)malloc(9 * sizeof(int*)); 
    for (int i = 0; i < 9; i++) pboard[i] = board[i];
    printf("%d\n", hidden_singles(pboard));
    // return board
    for (int m = 0; m < 81; ++m){
        int i = m / 9, j = m % 9;
        // update string
        int ctr = 2 * (9 * i + j);
        myStr[ctr] = tochar(pboard[i][j].cand + 5);
        myStr[ctr + 1] = tochar(pboard[i][j].cand);
    }
    free(pboard);
    printf("%s\n", myStr);
    return 0;
}