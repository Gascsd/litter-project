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

void menu2()
{
	printf("-------------------\n");
	printf("***  1. �Ų���  ***\n");
	printf("***  2. �����  ***\n");
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
		printf("������Ҫ�Ų������:>");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			//'*' '#' ' '
			if (show[x][y] == '*' || show[x][y] == '#')
			{
				if (mine[x][y] == '1')
				{
					printf("���ź�����ը����\n");
					flag = -1;//��־�ű�ը����
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
				printf("�������Ѿ����Ų������\n");
			}
			break;
		}
		else
		{
			printf("���������������������\n");
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
		printf("������Ҫ��ǵ�����:>");
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
				printf("�������Ѿ�����ǻ��Ų������\n");
			}
			break;
		}
		else
		{
			printf("���������������������\n");
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
		printf("������Ҫִ�еĲ���:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("�Ų���\n");
			not_mine = SeekMine(mine, show, ROW, COL, not_mine);
			if(not_mine != -1)
				DisplayBoard(show, ROW, COL);
			break;
		case 2:
			printf("�����\n");
			ismine = MarkMine(mine, show, ROW, COL,ismine);
			DisplayBoard(show, ROW, COL);
			break;
		default:
			printf("�����������������\n");
		}
		if (ismine == EASY)
		{
			printf("��ϲ�㣬��Ϸʤ�����Ų�������е���\n");
			break;
		}
		if (not_mine == row * col - EASY)
		{
			printf("��ϲ�㣬��Ϸʤ�����Ų�������е���\n");
			break;
		}
		if (not_mine == -1)
			break;
	} while (1);
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
	//DisplayBoard(mine, ROW, COL);
	DisplayBoard(show, ROW, COL);
	//����
	FindMine(mine, show, ROW, COL);
}