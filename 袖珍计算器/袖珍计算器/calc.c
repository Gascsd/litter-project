#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

void menu()
{
	printf("********************************\n");
	printf("******  1.add    2.sub    ******\n");
	printf("******  3.mul    4.div    ******\n");
	printf("******  0.exit            ******\n");
	printf("********************************\n");
}

int add(int x, int y)
{
	return x + y;
}
int sub(int x, int y)
{
	return x - y;
}
int mul (int x, int y)
{
	return x * y;
}
int div(int x, int y)
{
	return x / y;
}


//int main()
//{
//	int input = 0;
//	int x = 0;
//	int y = 0;
//	int ret = 0;
//	do
//	{
//		menu();//调用菜单函数
//		printf("请输入要进行的操作:>\n");
//		scanf("%d", &input);//输入选择功能
//		switch (input)
//		{
//		case 1:
//			printf("请输入两个操作数:>\n");
//			scanf("%d%d", &x, &y);
//			ret = add(x, y);
//			printf("结果是%d\n", ret);
//			break;
//		case 2:
//			printf("请输入两个操作数:>\n");
//			scanf("%d%d", &x, &y);
//			ret = sub(x, y);
//			printf("结果是%d\n", ret);
//			break;
//		case 3:
//			printf("请输入两个操作数:>\n");
//			scanf("%d%d", &x, &y);
//			ret = mul(x, y);
//			printf("结果是%d\n", ret);
//			break;
//		case 4:
//			printf("请输入两个操作数:>\n");
//			scanf("%d%d", &x, &y);
//			ret = div(x, y);
//			printf("结果是%d\n", ret);
//			break;
//		case 0:
//			printf("退出计算器\n");
//			break;
//		default:
//			printf("输入错误，请重新输入\n");
//		}
//	} while (input);
//	return 0;
//}



int main()
{
	int input = 0;
	int x = 0;
	int y = 0;
	int ret = 0;
	do
	{
		menu();//调用菜单函数
		printf("请输入要进行的操作:>\n");
		scanf("%d", &input);//输入选择功能
		if (input > 0 && input <= 4)
		{
			printf("请输入两个操作数:>\n");
			scanf("%d%d", &x, &y);
			int (*pf[5])(int, int) = { 0,add,sub,mul,div };//定义函数指针数组
			ret = pf[input](x, y);//通过input的值调用函数
			printf("结果是%d\n", ret);
		}
		else if (input == 0)
		{
			printf("退出\n");
			break;
		}
		else
		{
			printf("输入错误，请重新输入\n");
		}
	} while (input);
	return 0;
}


