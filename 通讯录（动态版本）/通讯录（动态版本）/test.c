#define _CRT_SECURE_NO_WARNINGS 1

#include"contact.h"


//实现一个通讯录；
//通讯录可以用来存储1000个人的信息，每个人的信息包括：姓名、性别、年龄、电话、住址
//提供方法：
//1.添加联系人信息
//2.删除指定联系人信息
//3.查找指定联系人信息
//4.修改指定联系人信息
//5.显示所有联系人信息
//6.清空所有联系人
//7.以名字排序所有联系人
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
		case 1:
			ContactAdd(&con);
			break;
		case 2:
			ContactDel(&con);
			break;
		case 3:
			ContactSearch(&con);
			break;
		case 4:
			ContactModify(&con);
			break;
		case 5:
			ContactShow(&con);
			break;
		case 6:
			ContactDestroy(&con);
			ContactInit(&con);
			break;
		case 7:
			ContactSort(&con);
			break;
		case 0:
			printf("退出\n");
			break;
		default:
			printf("输入错误，请重新输入...\n");
		}
	} while (input);
	return 0;
}
