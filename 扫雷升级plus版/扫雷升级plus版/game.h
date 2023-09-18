#pragma once

#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2
#define EASY 5


void menu();
void menu2();
void game();
void InitBoard(char board[ROWS][COLS], int row, int col, char set);
void DisplayBoard(char board[ROWS][COLS], int row, int col);
void SetMine(char board[ROWS][COLS], int row, int col);
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);
void SeekMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);
int MarkMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int ismine);
void UnfoldBoard(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y);
int isWin(char show[ROWS][COLS], int row, int col);
