#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"

int main()
{
	srand((unsigned int)time(NULL));//设置随机数起点
	int input = 0;
	do
	{
		menu();
		printf("please input:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("start game\n");
			game();
			break;
		case 0:
			printf("exit\n");
			break;
		default:
			printf("输入错误，请重新输入\n");
		}
	} while (input);
	return 0;
}