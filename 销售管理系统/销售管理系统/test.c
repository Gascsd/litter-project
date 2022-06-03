#define _CRT_SECURE_NO_WARNINGS 1

#include "system.h"

int main()
{
	Node pe[PEO_NUM];
	int m, n = 12;     //m为实际销售员人数，n为月份，定为12 
	int item;
	printf("请输入销售员总人数:");
	scanf("%d", &m);
	while (1)
	{
		item = Menu2();     //菜单显示,获取用户选择的选项
		switch (item)
		{
		case 1:
			Input_people(pe, m, n);  //录入信息
			getchar();
			getchar();
			break;
		case 2:
			Name(pe, m, n); 	//查找信息
			getchar();
			break;
		case 3:
			ModifySales(pe, m, n);   //修改信息
			getchar();
			break;
		case 4:
			Deleteinfor(pe, m, n);  //删除信息
			getchar();
			break;
		case 5:
			StatisticsSales(pe, m, n); //统计总销售额
			getchar();
			break;
		case 6:
			FA(pe, m, n);         //找出最值
			getchar();
			break;
		case 0:
			exit(0);             //退出 
			printf("程序结束\n");
			getchar();
			break;
		default:
			printf("\n\n输入的命令不正确，请重新输入!\n");
			getchar();
			break;
		}
	}
}