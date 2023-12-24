#include "sudoku.h"
#include "naked_pairs.h"

int isNakedPair(struct cell a, struct cell b){
  return (nonzeroes(a.cand, 1, 10) == 2 && // a has 2 candidates
          nonzeroes(b.cand, 1, 10) == 2 && // b has 2 candidates
          compArr(a.cand, b.cand, 10)); // they match
}

int naked_pairs(struct cell board[9][9]){ 
    int solved = 0;
    for (int m = 0; m < 81; m++){
        int i = m / 9, j = m % 9;
            if (board[i][j].num == 0){
                int value = 0, k, l;
                // (each k onwards is the other cell to find)
                for (k = 0; k < 9; k++) 
                    if (j != k && isNakedPair(board[i][j], board[i][k])){ // check in row 
                        solved++;
                        for (l = 0; l < 9; l++) // sweep in row
                            if (l != j && l != k) 
                                for (int m = 1; m < 10; m++) board[i][l].cand[m] ^= board[i][k].cand[m];
                    }
                    if (i != k && isNakedPair(board[i][j], board[k][j])){ // check in col
                        solved++;
                        for (l = 0; l < 9; l++) // sweep in col
                            if (l != i && l != k) 
                                for (int m = 1; m < 10; m++) board[l][j].cand[m] ^= board[k][j].cand[m];
                    }
                    if ((i != (i / 3) * 3 + k / 3 || j != (j / 3) * 3 + k % 3) && // check in box, chosen cell is not same  
                    isNakedPair(board[i][j], board[(i / 3) * 3 + k / 3][(j / 3) * 3 + k % 3])){ // 2 matching candidates
                        solved++;
                        for (l = 0; l < 9; l++) // sweep in box
                            if (l != k && (i != ((i / 3) * 3 + l / 3) || j != ((j / 3) * 3 + l % 3))) // chosen cell is not same
                                for (int m = 1; m < 10; m++) // eliminate all other instances of the candidates
                                    board[(i / 3) * 3 + l / 3][(j / 3) * 3 + l % 3].cand[m] ^= board[(j / 3) * 3 + k % 3][(j / 3) * 3 + k % 3].cand[m];
                    }
        }
    }
    return solved;
}
