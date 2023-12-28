#include "sudoku.h"
#include "hidden_pairs.h"

int hidden_pairs(struct cell **pboard){
    int solved = 0;
    for (int m = 0; m < 81; m++){
            int i = m / 9, j = m % 9;
            // going through all cells, delete all potentials that are written or noted
            if (pboard[i][j].num == 0){ // if not filled
                for (int k = 0; k < 9; k++){
                    if (j != k) // check with others in row
                        if (pboard[i][k].num != 0) pboard[i][j].row[pboard[i][k].num - 1] += 1; // if filled
                        else for (int l = 1; l < 10; l++) // otherwise go through its notes
                            if (pboard[i][k].cand[l] == 1) pboard[i][j].row[l - 1] += 1; // '1' is no

                    if (i != k) // check with others in col
                        if (pboard[k][j].num != 0) pboard[i][j].col[pboard[k][j].num - 1] += 1;
                        else for (int l = 1; l < 10; l++)
                            if (pboard[k][j].cand[l] == 1) pboard[i][j].col[l - 1] += 1; 

                    int box_i = i / 3 * 3 + k / 3, box_j = j / 3 * 3 + k % 3;
                    if (i != box_i || j != box_j) // check with others in box
                        if (pboard[box_i][box_j].num != 0) 
                            pboard[i][j].box[pboard[box_i][box_j].num - 1] += 1;
                        else for (int l = 1; l < 10; l++)
                            if (pboard[box_i][box_j].cand[l] == 1) pboard[i][j].box[l - 1] += 1;    
                }
                int row1 = 0, col1 = 0, box1 = 0; // entries of 1 in these arrays
                for (int k = 0; k < 9; k++){
                    if (pboard[i][j].row[k] == 1) row1++;
                    if (pboard[i][j].col[k] == 1) col1++;
                    if (pboard[i][j].box[k] == 1) box1++;   
                }
                solved = (row1 * (row1 - 1) + col1 * (col1 - 1) + box1 * (box1 - 1)) / 2;
        }
    }
    return solved;
}