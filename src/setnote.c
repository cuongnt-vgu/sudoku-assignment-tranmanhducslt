#include "sudoku.h"
#include "setnote.h"

void setnote(struct cell **pboard){
    int solved = 0;
    for (int m = 0; m < 81; m++){
            int i = m / 9, j = m % 9;
            if (pboard[i][j].num > 0){
                for (int k = 1; k <= 9; k++){
                    pboard[i][j].cand[0] = 1;
                    if (k != pboard[i][j].num) pboard[i][j].cand[k] = 0;
                    else pboard[i][j].cand[k] = 1;
                }
            }
            // going through all cells, delete all potentials that are written only
            else { // if not filled
                for (int k = 0; k < 9; k++){
                if (j != k) // check with others in row
                        if (pboard[i][k].num != 0) pboard[i][j].cand[pboard[i][k].num] = 0; 
                if (i != k) // check with others in col
                        if (pboard[k][j].num != 0) pboard[i][j].cand[pboard[k][j].num] = 0; 
                int box_i = i / 3 * 3 + k / 3, box_j = j / 3 * 3 + k % 3;
                if (i != box_i || j != box_j) // check with others in box
                    if (pboard[box_i][box_j].num != 0) 
                        pboard[i][j].cand[pboard[box_i][box_j].num] = 0;
                }
            }
    }
}