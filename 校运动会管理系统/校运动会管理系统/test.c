#define _CRT_SECURE_NO_WARNINGS 1

#include"system.h"

int main()
{
	proj* phead = NULL;
	read_file(&phead);
	int input = 0;
	do
	{
		menu();
		printf("������:>\n");
		scanf("%d", &input);
		switch (input)
		{
		case Exit:		
			save_file(&phead);
			printf("�˳�\n");
			return 0;
			break;
		case creat:
			Creat(&phead);
			break;
		case search:
			Search(phead);
			break;
		case revise:
			Revise(&phead);
			break;
		case delete:
			Delete(&phead);
			break;
		case print:
			Print(phead);
			break;
		case stats_project:
			Stats_project(&phead);
			break;
		default:
			printf("����������������룡\n");
			system("pause");
			system("cls");
		}
	} while (input);
	return 0;
}