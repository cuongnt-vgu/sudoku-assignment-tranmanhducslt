#include "sudoku.h"
#include "naked_pairs.h"

int isNakedPair(struct cell a, struct cell b){
  return (nonzeroes(a.cand, 1, 9) == 2 && // a has 2 candidates
          nonzeroes(b.cand, 1, 9) == 2 && // b has 2 candidates
          compArr(a.cand, b.cand, 10)); // they match
}

int naked_pairs(struct cell **pboard){ 
    int solved = 0;
    for (int m = 0; m < 81; m++){
        int i = m / 9, j = m % 9;
            if (pboard[i][j].num == 0){
                int value = 0, k, l;
                // (each k onwards is the other cell to find)
                for (k = 0; k < 9; k++) 
                    if (j != k && isNakedPair(pboard[i][j], pboard[i][k])){ // check in row 
                        solved++;
                        for (l = 0; l < 9; l++) // sweep in row
                            if (l != j && l != k) 
                                for (int m = 1; m < 10; m++) pboard[i][l].cand[m] ^= pboard[i][k].cand[m];
                    }
                    if (i != k && isNakedPair(pboard[i][j], pboard[k][j])){ // check in col
                        solved++;
                        for (l = 0; l < 9; l++) // sweep in col
                            if (l != i && l != k) 
                                for (int m = 1; m < 10; m++) pboard[l][j].cand[m] ^= pboard[k][j].cand[m];
                    }
                    if ((i != (i / 3) * 3 + k / 3 || j != (j / 3) * 3 + k % 3) && // check in box, chosen cell is not same  
                    isNakedPair(pboard[i][j], pboard[(i / 3) * 3 + k / 3][(j / 3) * 3 + k % 3])){ // 2 matching candidates
                        solved++;
                        for (l = 0; l < 9; l++) // sweep in box
                            if (l != k && (i != ((i / 3) * 3 + l / 3) || j != ((j / 3) * 3 + l % 3))) // chosen cell is not same
                                for (int m = 1; m < 10; m++) // eliminate all other instances of the candidates
                                    pboard[(i / 3) * 3 + l / 3][(j / 3) * 3 + l % 3].cand[m] ^= pboard[(j / 3) * 3 + k % 3][(j / 3) * 3 + k % 3].cand[m];
                    }
        }
    }
    return solved;
}
