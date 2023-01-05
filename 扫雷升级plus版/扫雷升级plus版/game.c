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

void UnfoldBoard(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
	int i = 0;
	int j = 0;
	int count = 0;
	if (x > 0 && x <= ROW && y > 0 && y <= COL)//�ж������Ƿ�Ϸ�
	{
		for (i = -1; i <= 1; i++)
		{
			for (j = -1; j <= 1; j++)
			{
				count = get_mine_count(mine, x + i, y + j);
				if (count == 0)//�жϸ�λ����Χ��û����
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
		printf("������Ҫ�Ų������:>\n");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)//�ж������Ƿ�Ϸ�
		{
			if (show[x][y] == '*' || show[x][y] == '#')//�����λ��δ���Ų��
			{
				if (mine[x][y] != '1')//�����λ�ò�����
				{
					count = get_mine_count(mine, x, y);
					if(count == 0)//�жϸ�λ����Χ��û����
						UnfoldBoard(mine, show, x, y);
					//DisplayBoard(show, ROW, COL);
					else
					{
						show[x][y] = count + '0';
					}
				}
				else
				{
					printf("���ź�����ը����\n");
					flag = -1;//��־�ű�ը����
					DisplayBoard(mine, ROW, COL);
					break;
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
}

int MarkMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int ismine)
{
	int x = 0;
	int y = 0;
	while (1)
	{
		printf("������Ҫ��ǵ�����:>\n");
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
		printf("������Ҫִ�еĲ���:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("�Ų���\n");
			SeekMine(mine, show, ROW, COL);
			if (not_mine != -1)
				DisplayBoard(show, ROW, COL);
			break;
		case 2:
			printf("�����\n");
			ismine = MarkMine(mine, show, ROW, COL, ismine);
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
		int win = isWin(show, ROW, COL);
		if (win == EASY)
		{
			printf("��ϲ�㣬��Ϸʤ�����Ų�������е���\n");
			break;
		}
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