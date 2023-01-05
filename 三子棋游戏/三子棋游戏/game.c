#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"

void menu()
{
	printf("**************************\n");
	printf("*********1. play  ********\n");
	printf("*********0. exit  ********\n");
	printf("**************************\n");
}


void InitBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void DisplayBoard(char board[ROW][COL], int row, int col)
{
	//   |   |   
	//---|---|---
	//   |   |  
	//---|---|---
	//   |   |   
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);
			if (j < col - 1)
				printf("|");
		}
		printf("\n");
		if (i < row - 1)
		{
			for (j = 0; j < col; j++)
			{
				printf("---");
				if (j < col - 1)
					printf("|");
			}
			printf("\n");
		}
	}
}

void ManMove(char board[ROW][COL], int row, int col)
{
	int x = 1;
	int y = 1;
	while (1)
	{
		//输入要下的行和列
		printf("请输入要下的行和列:>");
		scanf("%d%d", &x, &y);
		//判断该位置是否合法
		if ((x > 0 && x <= 3) && (y > 0 && y <= 3))
		{
			if ((board[x - 1][y - 1] == ' '))
			{
				board[x - 1][y - 1] = '*';
				break;
			}
			else
			{
				printf("这个位置已经下过啦，请重新输入\n");
			}
		}
		else
		{
			printf("输入不合法，请重新输入\n");
		}
	}
	
}

void ComputerMove(char board[ROW][COL], int row, int col)
{
	while (1)
	{
		//随机产生x，y
		int x = rand() % row;
		int y = rand() % col;
		//判断x，y是否合法
		if ((x >= 0 && x < 3) && (y >= 0 && y < 3))
		{
			if ((board[x][y] == ' '))
			{
				board[x][y] = '#';
				break;
			}
		}
	}
}

char CheckWin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	//判断是否赢
	for (i = 0; i < row; i++)
	{
		if (board[i][1] == board[i][2] && board[i][2] == board[i][0] && board[i][0] != ' ')
			return board[i][1];
		if (board[1][i] == board[2][i] && board[1][i] == board[0][i] && board[1][i] != ' ')
			return board[1][i];
	}
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] != ' ')
		return board[1][1];
	if (board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[0][2] != ' ')
		return board[1][1];
	//判断棋盘是否满
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
				return 0;
		}
	}
	return -1;
}

void game()
{
	char ret = 0;
	char board[ROW][COL] = { 0 };
	InitBoard(board,ROW,COL);//初始化棋盘
	DisplayBoard(board, ROW, COL);//打印棋盘
	while (1)
	{
		printf("人下棋\n");
		ManMove(board, ROW, COL);	//人下棋
		DisplayBoard(board, ROW, COL);
		//判断是否赢
		//未分出胜负返回0，继续循环
		//棋盘已满，返回-1
		//分出胜负
		//若电脑赢返回#
		//若人赢返回*
		ret = CheckWin(board, ROW, COL);
		if (ret != 0)
		{
			break;
		}
		printf("电脑下棋\n");
		ComputerMove(board, ROW, COL);//电脑下棋
		DisplayBoard(board, ROW, COL);
		//判断是否赢
		ret = CheckWin(board, ROW, COL);
		if (ret != 0)
		{
			break;
		}
	}
	printf("\n");
	DisplayBoard(board, ROW, COL);
	if (ret == '*')
	{
		printf("恭喜你赢啦！！！\n");
	}
	if (ret == '#')
	{
		printf("很遗憾，你输了！！！\n");
	}
	if (ret == -1)
	{
		printf("游戏结束，平局\n");
	}
}


