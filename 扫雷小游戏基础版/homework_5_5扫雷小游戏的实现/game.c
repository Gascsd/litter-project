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
	printf("-------ɨ����Ϸ-------\n");
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
	printf("-------ɨ����Ϸ-------\n");
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

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int count = 0;
	int win = 0;
	while (win < row * col - EASY)
	{
		printf("������Ҫ�Ų������:>");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (show[x][y] != '*')
			{
				printf("�������Ѿ����Ų������\n");
			}
			else 
			{
				if (mine[x][y] == '1')
				{
					printf("��ϲ�㣬��ը����\n");
					DisplayBoard(mine, ROW, COL);
					break;
				}
				else
				{
					win++;
					count = get_mine_count(mine, x, y);
					show[x][y] = count + '0';
					DisplayBoard(show, ROW, COL);
				}
			}
		}
		else
		{
			printf("���������������������\n");
		}
	}
	if (win == row * col - EASY)
	{
		printf("���ź�����Ӯ��\n");
		DisplayBoard(mine, ROW, COL);
	}
}

void game()
{
	char mine[ROWS][COLS] = { 0 };//��Ų��õ��׵���Ϣ
	char show[ROWS][COLS] = { 0 };//����ų����׵���Ϣ
	//��ʼ������
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	//������
	SetMine(mine, ROW, COL);
	//��ӡ����
	DisplayBoard(show, ROW, COL);
	//DisplayBoard(mine, ROW, COL);
	//����
	FindMine(mine, show, ROW, COL);
}
