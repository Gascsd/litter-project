#define _CRT_SECURE_NO_WARNINGS 1

#include"system.h"

void menu()//菜单函数
{
	printf("*********************************************************\n");
	printf("************  	  校运动会管理系统           ************\n");
	printf("*********************************************************\n");
	printf("************      [1]新建比赛项目            ************\n");
	printf("************  	  [2]查询比赛信息            ************\n");
	printf("************      [3]修改比赛信息            ************\n");
	printf("************      [4]删除比赛信息            ************\n");
	printf("************      [5]输出比赛信息            ************\n");
	printf("************      [6]统计项目内学院成绩排名  ************\n");
	printf("************      [0]退出                    ************\n");
	printf("*********************************************************\n");
}

void read_file(proj** pphead)//读文件
{
	FILE* fp = fopen("sport.txt", "r");
	if (!fp)
		return;
	while (1)
	{
		proj* newnode = (proj*)malloc(sizeof(proj));
		if (newnode == NULL)
		{
			printf("文件读取失败！");
			exit(0);
		}
		else
		{
			if (fread(newnode, sizeof(proj), 1, fp) < 1)
				break;
			newnode->next = *pphead;
			*pphead = newnode;
		}
	}
	fclose(fp);
}

void save_file(proj** pphead)//保存文件
{
	FILE* fp = fopen("sport.txt", "w+");
	proj* tmp = *pphead;
	if (!fp)
		return;
	while (tmp)
	{
		fwrite(tmp, sizeof(proj), 1, fp);
		tmp = tmp->next;
	}
	fclose(fp);
}

void Creat(proj** pphead)//新建比赛项目
{
	int num = 0;//参加比赛的学院数量
	int i = 0;
	proj* newnode = (proj*)malloc(sizeof(proj));
	if (newnode == NULL)
	{
		printf("开辟空间失败！");
		exit(0);
	}
	printf("请输入项目名称：\n");
	//输入信息
	scanf("%s", newnode->project);
	printf("请输入参加该项目的学院数量：\n");
	scanf("%d", &num);
	newnode->num = num;
	for (i = 0; i < num; i++)
	{
		printf("请输入第%d个学院名称：\n",i+1);
		scanf("%s", newnode->name[i]);
		newnode->score[i] = 0;
		newnode->no[i] = 0;
	}
	newnode->next = NULL;
	//遍历结点,连接
	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		proj* tmp = *pphead;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = newnode;
	}
	printf("新建项目成功！\n");
	save_file(pphead);//同步文件内容
	system("pause");
	system("cls");
}

static proj* search_by_proj(proj* phead, char name[])//通过项目名称找到指定结点
{
	assert(phead);
	proj* tmp = phead;
	while (tmp != NULL)
	{
		if (strcmp(tmp->project, name) == 0)
		{
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

static PRINT(proj* tmp)//输出指定结点的信息
{
	int i = 0;//循环变量
	printf("\t项目名称：%s\n", tmp->project);
	printf("学院名称\t单项成绩\t单项名次\n");
	for (i = 0; i < tmp->num; i++)
	{
		printf("%s\t\t%.2lf\t\t%d\n", tmp->name[i], tmp->score[i], tmp->no[i]);
	}
}

void Search(proj* phead)//查询比赛信息
{
	int i = 0;//循环变量
	int input = 0;
	char name[40] = { 0 };
	//根据比赛项目查询：输出参加该项目的所有学院的信息
	//学院名称查询：输出该学院参加的所有项目信息
	while (1)
	{
		printf("请输入查询的方式：\n1.按比赛项目查询\n2.按学院名称查询\n");
		printf("请选择:>\n");
		scanf("%d", &input);
		if (input == 1)//按比赛项目查询
		{
			printf("请输入要查询的项目名称:>\n");
			scanf("%s", name);
			proj* tmp = search_by_proj(phead, name);
			if (tmp == NULL)
			{
				printf("找不到该项目\n");
			}
			else
			{
				//输出指定内容
				PRINT(tmp);
			}
			break;
		}
		else if (input == 2)//按学院名称查询
		{
			printf("请输入要查询的学院名称:>\n");
			scanf("%s", name);
			proj* tmp = phead;
			printf("项目名称\t单项成绩\t单项名次\n");
			while (tmp != NULL)
			{
				for (i = 0; i < tmp->num; i++)
				{
					if (strcmp(tmp->name[i], name) == 0)
					{
						printf("%s\t%.2lf\t%d\n", tmp->project, tmp->score[i], tmp->no[i]);
					}
				}
				tmp = tmp->next;
			}
			break;
		}
		else
		{
			printf("输入错误，请重新输入\n");
		}
	}
	system("pause");
	system("cls");

}
void Revise(proj** pphead)//修改比赛信息
{
	int input = 0;
	int i = 0;//循环变量
	int num = 0;//参赛学院个数
	char project[40] = { 0 };
	while (1)
	{
		printf("请选择\n1.修改项目\n2.修改分数\n");
		scanf("%d", &input);
		if (input == 1)//修改项目
		{
			printf("请输入要修改的项目名称:>\n");
			scanf("%s", project);
			proj* tmp = search_by_proj(*pphead, project);
			if (tmp == NULL)
			{
				printf("找不到该项目，退出:>\n");
			}
			else
			{
				printf("请输入修改后的项目名称:>\n");
				scanf("%s", tmp->project);
				printf("请输入参加该项目的学院数量：\n");
				scanf("%d", &num);
				tmp->num = num;
				for (i = 0; i < num; i++)
				{
					printf("请输入第%d个学院名称：\n", i + 1);
					scanf("%s", tmp->name[i]);
					tmp->score[i] = 0;
					tmp->no[i] = 0;
				}
				printf("修改完成\n");
			}
			break;
		}
		else if (input == 2)//修改分数
		{
			printf("请输入要修改的项目名称:>\n");
			scanf("%s", project);
			proj* tmp = search_by_proj(*pphead, project);
			if (tmp == NULL)
			{
				printf("找不到该项目，退出:>\n");
			}
			else
			{
				for (i = 0; i < tmp->num; i++)
				{
					printf("请输入%s学院的成绩", tmp->name[i]);
					scanf("%lf", &tmp->score[i]);
				}
				printf("修改完成\n");
			}
			break;
		}
		else
		{
			printf("输入错误，请重新输入\n");
		}
	}
	save_file(pphead);//同步文件信息
	system("pause");
	system("cls");

}
void Delete(proj** pphead)//删除比赛信息
{
	char project[40] = { 0 };
	printf("请输入需要删除的项目名称\n");
	scanf("%s", project);
	proj* tmp = *pphead;
	if (strcmp(tmp->project, project) == 0)
	{
		*pphead = tmp->next;
		free(tmp->next);
		tmp->next = NULL;
		printf("删除完成\n");
		save_file(pphead);//同步文件信息
		system("pause");
		system("cls");
		return;
	}
	while (tmp->next != NULL)
	{
		if (strcmp(tmp->next->project, project) == 0)
		{
			tmp->next = tmp->next->next;
			free(tmp->next);
			tmp->next = NULL;
			printf("删除完成\n");
			save_file(pphead);//同步文件信息
			system("pause");
			system("cls");
			return;
		}
		tmp = tmp->next;
	}
	printf("为找到该项目，退出:>\n");
	save_file(pphead);//同步文件信息
	system("pause");
	system("cls");
}
void Print(proj* phead)//输出比赛信息
{
	if (phead == NULL)
	{
		printf("没有比赛项目信息，无法输出！\n");
	}
	else
	{
		proj* tmp = phead;
		while (tmp != NULL)
		{
			PRINT(tmp);
			tmp = tmp->next;
		}
	}
	system("pause");
	system("cls");

}

static Swap(const void* x, const void* y, unsigned int size)
{
	unsigned int i = 0;//定义循环变量
	for (i = 0; i < size; i++)
	{
		char tmp = *((char*)x + i);
		*((char*)x + i) = *((char*)y + i);
		*((char*)y + i) = tmp;
	}
}

void Stats_project(proj** pphead)//统计项目内学院成绩排名
{
	int i = 0;//循环变量
	int j = 0;
	char project[40] = { 0 };
	printf("请输入要统计的项目名称:>\n");
	scanf("%s", project);
	proj* tmp = search_by_proj(*pphead, project);
	if (tmp == NULL)
	{
		printf("没有找到该项目，退出:>\n");
	}
	else
	{
		for (j = 0; j < tmp->num; j++)
		{
			for (i = 0; i < tmp->num - j + 1; i++)
			{
				if (tmp->score[i] < tmp->score[i + 1])
				{
					Swap(&tmp->score[i], &tmp->score[i + 1], sizeof(tmp->score[i]));
					Swap(&tmp->name[i], &tmp->name[i + 1], sizeof(tmp->name[i]));
				}
			}
		}
		for (i = 0; i < tmp->num; i++)
		{
			tmp->no[i] = i + 1;
		}
		printf("统计完成\n");
	}
	save_file(pphead);//同步文件信息
	system("pause");
	system("cls");
}
