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
	printf("-------扫雷游戏-------\n");
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
	printf("-------扫雷游戏-------\n");
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
	printf("***  1. 排查雷  ***\n");
	printf("***  2. 标记雷  ***\n");
	printf("-------------------\n");
}

int SeekMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int not_mine)
{
	int x = 0;
	int y = 0;
	int flag = 0;
	int count = 0;
	while (1)
	{
		printf("请输入要排查的坐标:>");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			//'*' '#' ' '
			if (show[x][y] == '*' || show[x][y] == '#')
			{
				if (mine[x][y] == '1')
				{
					printf("很遗憾，被炸死了\n");
					flag = -1;//标志着被炸死了
					DisplayBoard(mine, ROW, COL);
					break;
				}
				else
				{
					not_mine++;
					count = get_mine_count(mine, x, y);
					show[x][y] = count + '0';
					DisplayBoard(show, ROW, COL);
				}
			}
			else
			{
				printf("该坐标已经被排查过啦！\n");
			}
			break;
		}
		else
		{
			printf("输入坐标错误，请重新输入\n");
		}
	}
	if (flag == 0)
		return not_mine;
	else
		return flag;
}

int MarkMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int ismine)
{
	int x = 0;
	int y = 0;
	while (1)
	{
		printf("请输入要标记的坐标:>");
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
				printf("该坐标已经被标记或排查过啦！\n");
			}
			break;
		}
		else
		{
			printf("输入坐标错误，请重新输入\n");
		}
	}
	return ismine;
}

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int input = 0;
	int ismine = 0;
	int not_mine = 0;
	do
	{
		menu2();
		printf("请输入要执行的操作:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("排查雷\n");
			not_mine = SeekMine(mine, show, ROW, COL, not_mine);
			if(not_mine != -1)
				DisplayBoard(show, ROW, COL);
			break;
		case 2:
			printf("标记雷\n");
			ismine = MarkMine(mine, show, ROW, COL,ismine);
			DisplayBoard(show, ROW, COL);
			break;
		default:
			printf("输入错误，请重新输入\n");
		}
		if (ismine == EASY)
		{
			printf("恭喜你，游戏胜利，排查出了所有的雷\n");
			break;
		}
		if (not_mine == row * col - EASY)
		{
			printf("恭喜你，游戏胜利，排查出了所有的雷\n");
			break;
		}
		if (not_mine == -1)
			break;
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