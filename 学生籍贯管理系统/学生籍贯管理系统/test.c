#define _CRT_SECURE_NO_WARNINGS 1

#include"system.h"

student* phead = NULL;//定义头节点指针

int main()
{
	printf("欢迎使用学生籍贯信息管理系统!\n");
	read_file(&phead);//读文件
	int input = 0;
	while (1)
	{
		menu();//打印菜单
		printf("请选择:>\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			add(&phead);//增加信息
			break;
		case 2:
			revise(&phead);//修改信息
			break;
		case 3:
			find(phead);//查找信息
			break;
		case 4:
			dele(&phead);//删除信息
			break;
		case 5:
			print(phead);//打印信息
			break;
		case 0:
			printf("退出...\n");//退出
			save_file(&phead);
			return 0;
		default:
			printf("输入错误，请重新输入\n");
		}
	}
}
