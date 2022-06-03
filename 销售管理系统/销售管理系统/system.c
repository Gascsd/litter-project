#define _CRT_SECURE_NO_WARNINGS 1

#include"system.h"

int Menu2(void)
{
	int item;
	system("cls");   //清屏操作 
	printf("这是销售管理系统，请选择您要的操作:\n\n");
	printf("\t\t1:录入销售员的信息\n");
	printf("\t\t2:查找某个销售员某个月的销售额\n");
	printf("\t\t3:修改某个销售员某个月的销售额\n");
	printf("\t\t4:删除某个销售员的销售信息\n");
	printf("\t\t5:统计所有销售员的年度总销售额\n");
	printf("\t\t6:找出最大（或最小）的月销售额和年度总销售额\n");
	printf("\t\t0:退出\n");
	printf("\n\n请输入命令:");
	scanf("%d", &item);    //读用户选择的命令
	return item;
}

Node Input_people(Node pe[], int m, int n)
{
	int 	i, j;
	for (i = 0; i < m; i++)
	{
		printf("请输入第%i位销售员的代号、姓名、月销售额、年度总销售额\n", i + 1);
		printf("代    号：");
		scanf("%s", &pe[i].no);
		getchar();                  //过滤掉回车键
		printf("姓    名：");
		gets(pe[i].name);
		for (j = 0; j < n; j++)
		{
			printf("%d月份销售额:", j + 1);
			scanf("%f", &pe[i].sales[j]);
		}
		pe[i].total = 0;
	}
}

void Name(Node pe[], int m, int n)
{
	char sname[15];
	int i, flag = 0, k;
	printf("请输入要查找的销售员姓名:");
	scanf("%s", sname);
	printf("请输入要查找的月份：");
	scanf("%d", &k);
	for (i = 0; i < m; i++)
	{
		if (strcmp(sname, pe[i].name) == 0)
		{
			flag = 1;
			printf("%d月份销售额%f: ", k, pe[i].sales[k - 1]);
		}
	}
	if (flag == 0)
		printf("查无此人！\n");
}

void ModifySales(Node pe[], int m, int n)
{
	char sname[15];
	int i, q = 0, k;
	float s;
	printf("请输入销售员姓名:");
	scanf("%s", sname);
	printf("请输入月份：");
	scanf("%d", &k);
	for (i = 0; i < m; i++)
	{
		if (strcmp(sname, pe[i].name) == 0)
		{
			q = 1;
			printf("请输入要修改的数值:");
			scanf("%f", &s);
			pe[i].sales[k - 1] = s;
			break;
		}
	}
	if (q == 0)
		printf("查无此人！\n");

}


void Deleteinfor(Node pe[], int m, int n)
{
	char sname[15];
	int i, j, q, x;
	printf("请输入要删除信息的销售员姓名:");
	scanf("%s", sname);
	for (i = 0; i < m; i++)
	{
		if (strcmp(sname, pe[i].name) == 0)
		{
			q = 1;
			for (j = i; j < (m - 1); j++)
			{
				strcpy(pe[j].name, pe[j + 1].name);
				for (x = 0; x < n; x++)
				{
					pe[j].sales[x] = pe[j + 1].sales[x - 1];
				}
			}
		}
	}
	//pe[m - 1] = ;
	if (q == 0)
	{
		printf("查无此人！\n");
	}
	printf("删除成功！");
}


void StatisticsSales(Node pe[], int m, int n)
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			pe[i].total += pe[i].sales[j];
		}
	}
	for (i = 0; i < m; i++)
	{
		printf("姓    名：%s ,总销售额: %f", pe[i].name, pe[i].total);
		printf("\n");
	}

}

void FA(Node pe[], int m, int n)
{
	int i, j;
	float min1 = pe[0].sales[0];	//min1和max1分别为月销售额最大值和最小值
	float max1 = pe[0].sales[0];	//现将第一个人的第一月的销售额设为最小值和最大值 
	int num1 = 0, num2 = 0, month1 = 0, month2 = 0, num3 = 0, num4 = 0;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (min1 > pe[i].sales[j])
			{
				min1 = pe[i].sales[j];
				num1 = i;       //引入人名 
				month1 = j;     //计算月份 
			}
			if (max1 < pe[i].sales[j])
			{
				max1 = pe[i].sales[j];
				num2 = i;
				month2 = j;
			}
			pe[i].total += pe[i].sales[j];   //计算年度总销售额 
		}

	}

	float min2 = pe[0].total;  //min2和max2分别是年度总销售额最大值和最小值 
	float max2 = pe[0].total;
	for (i = 0; i < m; i++)
	{
		if (min2 > pe[i].total)
		{
			min2 = pe[i].total;
			num3 = i;
		}
		if (max2 < pe[i].total)
		{
			max2 = pe[i].total;
			num4 = i;
		}
	}
	printf("%s 的%d月销售额最小为%f：\n", pe[num1].name, month1 + 1, min1);
	printf("%s 的%d月销售额最大为%f:\n", pe[num2].name, month2 + 1, max1);
	printf("%s 的年度总销售额最小为%f：\n", pe[num3].name, min2);
	printf("%s 的年度总销售额最大为%f：\n", pe[num4].name, max2);
}

