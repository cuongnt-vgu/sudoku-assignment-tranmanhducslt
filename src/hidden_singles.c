#include "sudoku.h"
#include "hidden_singles.h"

int hidden_singles(struct cell board[9][9]){
    int solved = 0, count = 0, value;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){ // going through all cells
            if (board[i][j].num == 0){ // if not filled
                for (int k = 0; k < 9; k++){
                    if (j != k) // check with others in row
                        if (board[i][k].num != 0) board[i][j].row[board[i][k].num - 1] = 1; // if filled
                        else for (int l = 1; l < 10; l++) // otherwise go through its notes
                            if (board[i][k].cand[l] == 1) board[i][j].row[l - 1] = 1; // '1' is no

                    if (i != k) // check with others in col
                        if (board[k][j].num != 0) board[i][j].col[board[k][j].num - 1] = 1;
                        else for (int l = 1; l < 10; l++)
                            if (board[k][j].cand[l] == 1) board[i][j].col[l - 1] = 1; 

                    int box_i = i / 3 * 3 + k / 3, box_j = j / 3 * 3 + k % 3;
                    if (i != box_i || j != box_j) // check with others in box
                        if (board[box_i][box_j].num != 0) 
                            board[i][j].box[board[box_i][box_j].num - 1] = 1;
                        else for (int l = 1; l < 10; l++)
                            if (board[box_i][box_j].cand[l] == 1) board[i][j].box[l - 1] = 1;    
                }
                for (int k = 0; k < 9; k++)
                    if (board[i][j].row[k] * board[i][j].col[k] * board[i][j].box[k] == 0 && board[i][j].cand[k + 1]){
                        solved++; /* the next 3 lines are if need to fill in
                        board[i][j].num = k + 1;
                        board[i][j].cand[0] = 1;
                        break; */
                    }
            }
        }
    }
    return solved;
}