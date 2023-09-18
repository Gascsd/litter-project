#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"

void menu()
{
	printf("********************************\n");
	printf("*******1. play *****************\n");
	printf("*******2. exit *****************\n");
	printf("********************************\n");
}

void Shutdown()
{
	char input[20] = { 0 };
	printf("很遗憾，游戏失败\n");
	printf("你的电脑将在一分钟后关闭\n");
	system("shutdown -s -t 60");
	while (1)
	{
		printf("如果输入我是猪,关机将会被取消\n");
		scanf("%s", input);
		if (strcmp(input, "我是猪") == 0)
		{
			system("shutdown -a");
			printf("恭喜你对自己有了一个清醒的认知\n那么要不要再来一把呢\n");
			break;
		}
	}
}

void game()
{
	int count = 6;
	int n = 0;
	int ret = rand() % 100 + 1; 
	while (count)
	{
		printf("请猜一个数字\n");
		scanf("%d", &n);
		if (n > ret)
		{
			printf("猜大了\n你只剩下%d次机会啦\n",count - 1);
		}
		else if (n < ret)
		{
			printf("猜小了\n你只剩下%d次机会啦\n", count - 1);
		}
		else
		{
			printf("恭喜你猜对了，真棒\n那么要不要再来一次呢\n");
			break;
		}
		count--;
		printf("\n");
	}
	if (!count)
	{
		Shutdown();
	}
}

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("请选择(0/1)");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("玩游戏\n");
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("输入错误，请重新输入\n");
		}
		
	} while (input);
	return 0;
}