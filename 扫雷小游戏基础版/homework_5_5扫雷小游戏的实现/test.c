#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"

int main()
{
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("������:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("����Ϸ\n");
			game();
			break;
		case 0:
			printf("�˳�\n");
			break;
		default:
			printf("�����������������\n");
		}
	} while (input);
	return 0;
}