#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#define COL 3
#define ROW 3

void menu();
void game();
void InitBoard(char board[ROW][COL], int row, int col);
void DisplayBoard(char board[ROW][COL], int row, int col);
void ManMove(char board[ROW][COL], int row, int col);
void ComputerMove(char board[ROW][COL], int row, int col);
char CheckWin(char board[ROW][COL], int row, int col);
