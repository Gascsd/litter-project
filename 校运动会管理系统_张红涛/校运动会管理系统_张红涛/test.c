#define _CRT_SECURE_NO_WARNINGS 1

#include"system.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define LED sizeof(struct node)


struct node
{
	char xiangmu[40];
	char name[10][40];
	float score[10];
	int no[10];
	struct node* link;
};
struct node* head = NULL;


void ReadFile()
{
	FILE* f = fopen("sports.txt", "r");
	if (!f)//永远为真
		return;
	while (1)
	{
		struct node* temp = NULL;
		struct node* nd = (struct node*)malloc(LED);
		if (nd == NULL)
		{
			exit(-1);
		}
		else
		{
			if (fread(nd, LED, 1, f) < 1)
			{
				break;
			}
			temp = head;
			nd->link = NULL;
			head = nd;
			nd->link = temp;
		}
	}
	fclose(f);
}
void SaveFile()
{
	struct node* temp = NULL;
	FILE* f = fopen("sports.txt", "w+");
	if (!f)
		return;
	temp = head;
	while (temp)
	{
		fwrite(temp, LED, 1, f);
		temp = temp->link;
	}

	fclose(f);
}


/*
链表头插法
*/
void in()
{
	//参与该项目的学院数量
	int m = 0;
	int a = 0;
	struct node* p = NULL;
	struct node* q = NULL;
	p = (struct node*)malloc(LED);
	if (p == NULL)
	{
		exit(-1);
	}
	q = head;
	memset(p->no, -1, sizeof(p->no));
	p->link = NULL;
	head = p;
	p->link = q;

	printf("请输入运动会项目名称:\n");
	scanf("%s", p->xiangmu);
	printf("请输入参与该项目的学院数量:\n");
	scanf("%d", &m);
	for (a = 0; a < m; a++)
	{
		printf("请输入第%d个学院名称:\n", a + 1);
		scanf("%s", p->name[a]);
		printf("请输入该运动项目成绩:\n");
		scanf("%f", &p->score[a]);
		p->no[a] = 0;
	}
	printf("该项运动信息输入完成!\n");

}
//查看某个运动情况
void find()
{
	int i = 0;
	struct node* q = NULL;
	char name[40] = { 0 };
	printf("请输入运动名称:\n");
	scanf("%s", name);
	q = head;
	while (q)
	{
		//找到对应的运动
		if (strcmp(q->xiangmu, name) == 0)
		{
			//显示各个学院参与该项目情况
			for (i = 0; i < 10; i++)
			{
				if (q->no[i] == -1)
					break;
				printf("学院名称:%s，项目分数:%.2f\n", q->name[i], q->score[i]);
			}
			return;
		}
		q = q->link;
	}
	printf("没有找到对应的运动项目\n");
}
void xg()
{
	int a = 0;
	int b = 0;
	struct node* q = NULL;
	char Nname[40] = { 0 };
	printf("请输入要修改的运动名称:\n");
	scanf("%s", Nname);
	q = head;
	while (q)
	{
		if (strcmp(q->xiangmu, Nname) == 0)
		{
			//修改项目信息
			printf("请输入参与该项目的学院数量:\n");
			scanf("%d", &a);
			memset(q->no, -1, sizeof(q->no));
			for (b = 0; b < a; b++)
			{
				printf("请输入第%d个学院名称:\n", b + 1);
				scanf("%s", q->name[b]);
				printf("请输入该运动项目成绩:\n");
				scanf("%f", &q->score[b]);
				q->no[b] = 0;
			}
			return;
		}
		q = q->link;
	}
}
void del()
{
	struct node* temp = NULL;
	struct node* prev = NULL;
	char sport_name[40] = { 0 };
	printf("请输入要删除的运动名称:\n");
	scanf("%s", sport_name);
	temp = head;
	prev = NULL;
	while (temp)
	{
		//从列表中删除运动项目
		if (strcmp(sport_name, temp->xiangmu) == 0)
		{
			if (prev)
			{
				prev->link = temp->link;
			}
			else
			{
				head = temp->link;
			}
			printf("删除项目%s成功！\n", sport_name);
			free(temp);
			return;
		}
		prev = temp;
		temp = temp->link;
	}
	printf("没有找到对应的运动项目!\n");
}

//总成绩排名
void zpm()
{
	int i = 0, j = 0;
	int found = 0;
	int name_index = 0;
	char tn[40] = { 0 };
	char name[10][40] = { 0 };
	float total_score[10] = { 0 };
	struct node* temp = head;
	while (temp)
	{
		for (i = 0; i < 10; i++)
		{
			if (temp->no[i] == -1)//判断是否还有学院参加这项运动
				break;

			for (j = 0; j < 10; j++)
			{
				if (strlen(name[j]) < 1)//判断是否还有学院参加这项运动
				{
					name_index = j;
					break;
				}
				if (strcmp(name[j], temp->name[i]) == 0)
				{
					name_index = j;
					found = 1;
					break;
				}
			}
			if (found == 0)
			{
				strcpy(name[name_index], temp->name[i]);
			}
			found = 0;
			total_score[name_index] = total_score[name_index] + temp->score[i];
		}
		temp = temp->link;
	}

	//排序
	for (i = 0; i < 10; i++)
	{
		for (j = i; j < 10; j++)
		{
			if (total_score[i] < total_score[j])
			{
				float t = total_score[i];
				total_score[i] = total_score[j];
				total_score[j] = t;
				strcpy(tn, name[i]);
				strcpy(name[i], name[j]);
				strcpy(name[j], tn);
			}

		}
	}
	printf("运动会总成绩排名:\n");
	for (i = 0; i < 10; i++)
	{
		if (total_score[i] == 0)
			break;
		printf("第%d名:%s,总分:%.2f\n", i + 1, name[i], total_score[i]);
	}
}
//每个项目学院排名
void dpm()
{
	char tn[40] = { 0 };
	char name[10][40] = { 0 };
	float total_score[10] = { 0 };
	struct node* temp = NULL;
	int i = 0;
	int j = 0;
	temp = head;
	printf("运动会单项运动排名\n");
	while (temp)
	{
		for (i = 0; i < 10; i++)
		{
			total_score[i] = -1;
		}
		//临时赋值
		for (i = 0; i < 10; i++)
		{
			if (temp->no[i] == -1)
				break;
			strcpy(name[i], temp->name[i]);
			total_score[i] = temp->score[i];
		}
		//排序
		for (i = 0; i < 10; i++)
		{
			for (j = i; j < 10; j++)
			{
				if (total_score[i] < total_score[j])
				{
					float ts = total_score[i];
					total_score[i] = total_score[j];
					total_score[j] = ts;
					strcpy(tn, name[i]);
					strcpy(name[i], name[j]);
					strcpy(name[j], tn);
				}
			}
		}
		printf("运动会项目 %s 排名:\n", temp->xiangmu);		//显示该项目排名
		for (i = 0; i < 10; i++)
		{
			if (total_score[i] < 0)
				break;
			printf("第%d名:%s，分数%.2f\n", i + 1, name[i], total_score[i]);
		}
		printf("\n");
		temp = temp->link;
	}
}
void Menu()
{
	//隐藏功能：同步文件功能
	system("cls");
	printf("\n校运动会项目管理系统，请输入你要执行的的操作：\n\n");
	printf("\t\t|--------------校运会项目管理系统-------------|\n");
	printf("\t\t|1.录入运动会项目的相关信息                   |\n");
	printf("\t\t|2.查找某个项目的信息                         |\n");
	printf("\t\t|3.修改某个项目的信息                         |\n");
	printf("\t\t|4.删除某个项目的信息                         |\n");
	printf("\t\t|5.学院单项成绩排名                           |\n");
	printf("\t\t|6.学院的总成绩排名                           |\n");
	printf("\t\t|0.退出系统                                   |\n");
	printf("\t\t|---------------------------------------------|\n");
	printf("请输入你所要执行的功能对应的数字0-6：\n");
	system("pause");
}
void one()
{
	int a, b, c, d, e;
	for (a = 6;; a++)
	{
		b = (a - 1) / 5 * 4;  //a是A看到的鱼， 所以a-1除以5，再乘上4，就是B醒来看到的鱼。下同 
		c = (b - 1) / 5 * 4;
		d = (c - 1) / 5 * 4;
		e = (d - 1) / 5 * 4;
		if (a % 5 == 1 && b % 5 == 1 && c % 5 == 1 && d % 5 == 1 && e % 5 == 1)
		{
			printf("五人至少合伙捕了 %d 条鱼。\n", a);
			break;//此处是算出符合条件的最小数值，避免出现无限循环
		}
	}
}
void two()
{
	double x, y, pi;//x,y是两个随机数字，pi就是圆周率
	int n, s;//n是落入半径为一的四分之一圆内的点数，s是总共随机出来的点数。
	n = s = 0;
	while (s <= 10000000)
	{
		x = rand() / 32767.0;//rand()是产生随机整数的函数再除以32767.0得到的数字是处于0-1之间的随机数字
		y = rand() / 32767.0;//同上
		if ((x * x + y * y) <= 1)
			n++;//if语句统计出在1/4圆内的点
		s++;//统计总共的点数
	}
	pi = (4.0 * n) / 10000000;//因为n/s=1/4圆的面积/边长为一的正方形的面积；pi/4=n/s ->pi=(4*n)/s
	printf("圆周率约等于%1f\n", pi);
}
void three()
{
	double r = 1, n, x = 0.5;//创建两个变量，分别用来保存，正多边形的边数，第一个正多边形（正六边形）的半径的一半 ,r是半径为一的单位圆，pi是要求的圆周率
	for (n = 6; x > 1e-15; n *= 2)//1e-15代表的是10^-15次方，也就是0.000000000000001，确保x的有效值在double的精度范围内 
	{
		x = hypot(x, 1 - sqrt(1 - x * x)) / 2;//hypot为求直角三角形斜边的函数(求直角三角形斜边的函数),设x为正六边形边长的一半，那么x就是下一个正N边形的边长的1/2
	}////这里省略了，因为pai=c/d ->pai=2*x*i/2*1 ->pai=x*i ，.15表示的是小数点后15位 
	printf("%.15f\n ", x * n);
	printf("%.15f\n", 1e-15);
}
void nMenu()
{
	system("cls");
	printf("1.捕鱼和分鱼 2.随机法求PI 3.正多边形求PI 4.校运动会项目管理 5.退出\n");

}
void Sports()
{
	char menu = 0;
	ReadFile();
	while (1)
	{
		Menu();
		menu = getchar();
		switch (menu)
		{
		case '1':
			in();
			SaveFile();
			break;
		case '2':
			find();
			break;
		case '3':
			xg();
			break;
		case '4':
			del();
			SaveFile();
			break;
		case '5':
			dpm();
			break;
		case '6':
			zpm();
			break;
		case '0':
			exit(0);
			return;
		case '\n':
			system("cls");
			continue;
		default:
			printf("输入错误，请重新输入\n");
			break;
		}
		system("pause");
		system("cls");
	}
}
int main()
{
	char pmenu = 0;
	int item = 0;
	while (1)
	{
		nMenu();
		pmenu = getchar();
		switch (pmenu)
		{
		case '1':
			one();
			break;
		case '2':
			two();
			break;
		case '3':
			three();
			break;
		case '4':
			Sports();
			break;
		case '5':
			return 0;
		case '\n':
			//system("cls");
			item = 1;
			break;
		default:
			printf("输入错误，请重新输入\n");
			break;
		}
		if (item == 0)
		{
			system("pause");
			system("cls");
		}
		else
		{
			item = 0;
		}
	}

	return 0;
}
