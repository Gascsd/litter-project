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
	printf("���ź�����Ϸʧ��\n");
	printf("��ĵ��Խ���һ���Ӻ�ر�\n");
	system("shutdown -s -t 60");
	while (1)
	{
		printf("�������������,�ػ����ᱻȡ��\n");
		scanf("%s", input);
		if (strcmp(input, "������") == 0)
		{
			system("shutdown -a");
			printf("��ϲ����Լ�����һ�����ѵ���֪\n��ôҪ��Ҫ����һ����\n");
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
		printf("���һ������\n");
		scanf("%d", &n);
		if (n > ret)
		{
			printf("�´���\n��ֻʣ��%d�λ�����\n",count - 1);
		}
		else if (n < ret)
		{
			printf("��С��\n��ֻʣ��%d�λ�����\n", count - 1);
		}
		else
		{
			printf("��ϲ��¶��ˣ����\n��ôҪ��Ҫ����һ����\n");
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
		printf("��ѡ��(0/1)");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("����Ϸ\n");
			game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("�����������������\n");
		}
		
	} while (input);
	return 0;
}