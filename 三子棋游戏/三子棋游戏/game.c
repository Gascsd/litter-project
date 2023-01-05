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
		//����Ҫ�µ��к���
		printf("������Ҫ�µ��к���:>");
		scanf("%d%d", &x, &y);
		//�жϸ�λ���Ƿ�Ϸ�
		if ((x > 0 && x <= 3) && (y > 0 && y <= 3))
		{
			if ((board[x - 1][y - 1] == ' '))
			{
				board[x - 1][y - 1] = '*';
				break;
			}
			else
			{
				printf("���λ���Ѿ��¹���������������\n");
			}
		}
		else
		{
			printf("���벻�Ϸ�������������\n");
		}
	}
	
}

void ComputerMove(char board[ROW][COL], int row, int col)
{
	while (1)
	{
		//�������x��y
		int x = rand() % row;
		int y = rand() % col;
		//�ж�x��y�Ƿ�Ϸ�
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
	//�ж��Ƿ�Ӯ
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
	//�ж������Ƿ���
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
	InitBoard(board,ROW,COL);//��ʼ������
	DisplayBoard(board, ROW, COL);//��ӡ����
	while (1)
	{
		printf("������\n");
		ManMove(board, ROW, COL);	//������
		DisplayBoard(board, ROW, COL);
		//�ж��Ƿ�Ӯ
		//δ�ֳ�ʤ������0������ѭ��
		//��������������-1
		//�ֳ�ʤ��
		//������Ӯ����#
		//����Ӯ����*
		ret = CheckWin(board, ROW, COL);
		if (ret != 0)
		{
			break;
		}
		printf("��������\n");
		ComputerMove(board, ROW, COL);//��������
		DisplayBoard(board, ROW, COL);
		//�ж��Ƿ�Ӯ
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
		printf("��ϲ��Ӯ��������\n");
	}
	if (ret == '#')
	{
		printf("���ź��������ˣ�����\n");
	}
	if (ret == -1)
	{
		printf("��Ϸ������ƽ��\n");
	}
}


