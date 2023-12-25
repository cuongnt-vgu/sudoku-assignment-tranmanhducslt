#include <stdio.h>
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

void convert(char n, int *s){
    int m = 0, i = 0;
    while (map[m] != n) m++;
    // number to reversed binary
    while (m > 0){
        s[i] = (m % 2);
        i++; m /= 2;
    }
}

int main(){
    FILE *fptr;
        fptr = fopen("sudokustr.txt", "r");
	if (fptr == NULL){
		printf("Cannot find file\n");
		return 1;
	}
    char myStr[163]; // must add 1 for the '\0'
    fgets(myStr, 163, fptr);
	for (int m = 0; m < 81; ++m){
	    int i = m / 9, j = m % 9;
		int ctr = 2 * (9 * i + j);
        convert(myStr[ctr], (board[i][j].cand + 5));
        convert(myStr[ctr + 1], board[i][j].cand);
        if (board[i][j].cand[0] == 1)
            for (int k = 1; k < 10; ++k)
                if (board[i][j].cand[k] == 1){
                    board[i][j].num = k;
                    break;
                }
    }
    //printf("%d\n", hidden_singles(board));
    //printf("%d\n", naked_pairs(board));
    //printf("%d\n", hidden_pairs(board));
    return 0;
}
