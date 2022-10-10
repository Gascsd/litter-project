#define _CRT_SECURE_NO_WARNINGS 1

#include"contact.h"


int main()
{
	Contact con;
	ContactInit(&con);
	int input = 0;
	do
	{
		menu();
		printf("请输入:>");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			ContactAdd(&con);
			break;
		case DEL:
			ContactDel(&con);
			break;
		case SEARCH:
			ContactSearch(&con);
			break;
		case MODIFY:
			ContactModify(&con);
			break;
		case SHOW:
			ContactShow(&con);
			break;
		case SORT:
			ContactSort(&con);
			break;
		case EXIT:
			SaveFile(&con);
			ContactDestroy(&con);
			printf("退出\n");
			break;
		default:
			printf("输入错误，请重新输入...\n");
		}
	} while (input);
	return 0;
}
