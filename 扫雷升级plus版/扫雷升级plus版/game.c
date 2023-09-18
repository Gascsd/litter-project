#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"

void menu()
{
	printf("***************************************\n");
	printf("*************** 1. play  **************\n");
	printf("*************** 0. exit  **************\n");
	printf("***************************************\n");
}

void InitBoard(char board[ROWS][COLS], int row, int col, char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = set;
		}
	}
}

void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	printf("-------game-------\n");
	int i = 0;
	int j = 0;
	for (i = 0; i <= col; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("-------game-------\n");
}

void SetMine(char board[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int count = EASY;
	while (count)
	{
		x = rand() % row + 1;
		y = rand() % col + 1;
		if (x > 0 && x < ROWS && y>0 && y < COLS)
		{
			if (board[x][y] == '0')
			{
				board[x][y] = '1';
				count--;
			}
		}
	}
}

int get_mine_count(char board[ROWS][COLS], int x, int y)
{
	return board[x - 1][y - 1] +
		board[x][y - 1] +
		board[x + 1][y - 1] +
		board[x - 1][y] +
		board[x + 1][y] +
		board[x - 1][y + 1] +
		board[x][y + 1] +
		board[x + 1][y + 1] - 8 * '0';
}

void menu2()
{
	printf("-------------------\n");
	printf("***  1. Check  ***\n");
	printf("***  2. Markers  ***\n");
	printf("-------------------\n");
}

void UnfoldBoard(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
	int i = 0;
	int j = 0;
	int count = 0;
	if (x > 0 && x <= ROW && y > 0 && y <= COL)//判断坐标是否合法
	{
		for (i = -1; i <= 1; i++)
		{
			for (j = -1; j <= 1; j++)
			{
				count = get_mine_count(mine, x + i, y + j);
				if (count == 0)//判断该位置周围有没有雷
				{
					if (show[x + i][y + j] == '*' || show[x + i][y + j] == '#')
					{
						show[x + i][y + j] = ' ';
						UnfoldBoard(mine, show, x + i, y + j);
					}
				}
			}
		}
	}
}

void SeekMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int flag = 0;
	int count = 0;
	while (1)
	{
		printf("please input Point:>\n");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)//判断坐标是否合法
		{
			if (show[x][y] == '*' || show[x][y] == '#')//如果该位置未被排查过
			{
				if (mine[x][y] != '1')//如果该位置不是雷
				{
					count = get_mine_count(mine, x, y);
					if(count == 0)//判断该位置周围有没有雷
						UnfoldBoard(mine, show, x, y);
					//DisplayBoard(show, ROW, COL);
					else
					{
						show[x][y] = count + '0';
					}
				}
				else
				{
					printf("Unfortunately, he was blown up\n");
					flag = -1;//标志着被炸死了
					DisplayBoard(mine, ROW, COL);
					break;
				}
			}
			else
			{
				printf("The coordinates have already been checked！\n");
			}
			break;
		}
		else
		{
			printf("Enter coordinates incorrectly, please re-enter\n");
		}
	}
}

int MarkMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int ismine)
{
	int x = 0;
	int y = 0;
	while (1)
	{
		printf("Please enter the coordinates you want to mark:>\n");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (show[x][y] == '*')
			{
				show[x][y] = '#';
				ismine++;
				break;
			}
			else
			{
				printf("The coordinates have already been flagged or checked！\n");
			}
			break;
		}
		else
		{
			printf("Enter coordinates incorrectly, please reenter\n");
		}
	}
	return ismine;
}

int isWin(char show[ROWS][COLS], int row, int col)
{
	int count = 0;
	for (int i = 1; i <= row; i++)
	{
		for (int j = 1; j <= col; j++)
		{
			if (show[i][j] == '*')
				count++;
		}
	}
	return count;
}

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int input = 0;
	int ismine = 0;
	int not_mine = 0;
	do
	{
		menu2();
		printf("Please enter the action to be performed:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("Scouring mine\n");
			SeekMine(mine, show, ROW, COL);
			if (not_mine != -1)
				DisplayBoard(show, ROW, COL);
			break;
		case 2:
			printf("Marker mine\n");
			ismine = MarkMine(mine, show, ROW, COL, ismine);
			DisplayBoard(show, ROW, COL);
			break;
		default:
			printf("Input error, please re-enter\n");
		}
		if (ismine == EASY)
		{
			printf("Congratulations, game of Thrones. We've identified all the Thunder\n");
			break;
		}
		int win = isWin(show, ROW, COL);
		if (win == EASY)
		{
			printf("Congratulations, game of Thrones. We've identified all the Thunder\n");
			break;
		}
	} while (1);
}


void game()
{
	char mine[ROWS][COLS] = { 0 };//存放布置的雷的信息
	char show[ROWS][COLS] = { 0 };//存放排除的雷的信息
	//初始化数组
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	//设置雷
	SetMine(mine, ROW, COL);
	//打印棋盘
	//DisplayBoard(mine, ROW, COL);
	DisplayBoard(show, ROW, COL);
	//排雷
	FindMine(mine, show, ROW, COL);
}