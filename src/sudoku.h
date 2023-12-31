#pragma once
#include <stdio.h>
#include <stdlib.h>

char map[32] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'};
struct cell{
	int num;
	int cand[10]; // 0. value as bool of presence; "1" for yes
    int row[9]; // bool of #s in its row, "1" for no
    int col[9]; // bool of #s in its col, "1" for no
    int box[9]; // bool of #s in its box, "1" for no
};

int nonzeroes(int test[], int L, int R);
int compArr(int a[], int b[], int size);
void convert(char n, int *s);
struct cell board[9][9] = {0, {0}, {0}, {0}, {0}}; // starting board