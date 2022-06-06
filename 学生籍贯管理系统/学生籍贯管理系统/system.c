#define _CRT_SECURE_NO_WARNINGS 1

#include"system.h"

void read_file(student** pphead)//读文件
{
	assert(pphead);
	FILE* fp = fopen("data.txt", "r");
	if (!fp)
		return;
	while (1)
	{
		student* newnode = (student*)malloc(sizeof(student));
		if (newnode == NULL)
		{
			printf("文件读取失败！");
			exit(0);
		}
		else
		{
			if (fread(newnode, sizeof(student), 1, fp) < 1)
				break;
			newnode->next = *pphead;
			*pphead = newnode;
		}
	}
	fclose(fp);
}

void save_file(student** pphead)//保存文件
{
	assert(pphead);
	FILE* fp = fopen("data.txt", "w+");
	student* tmp = *pphead;
	if (!fp)
		return;
	while (tmp)
	{
		fwrite(tmp, sizeof(student), 1, fp);
		tmp = tmp->next;
	}
	fclose(fp);
}

static Print(student* tmp)//输出指定内容
{
	printf("%s\t%s\t\t%s\t\t%s\t%s\n", tmp->no, tmp->name, tmp->tele, tmp->ID, tmp->jg);
}

static student* search(student* phead, char no[])//通过学号找到指定结点
{
	assert(phead);
	student* tmp = phead;
	while (tmp != NULL)
	{
		if (strcmp(tmp->no, no) == 0)
		{
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

void menu()//打印菜单
{
	printf("****************************************\n");
	printf("********** 学生籍贯管理系统 ************\n");
	printf("****************************************\n");
	printf("**********  1.增加学籍信息  ************\n");
	printf("**********  2.修改学籍信息  ************\n");
	printf("**********  3.查找学籍信息  ************\n");
	printf("**********  4.删除学籍信息  ************\n");
	printf("**********  5.打印学籍信息  ************\n");
	printf("**********  0.退出          ************\n");
	printf("****************************************\n");
}

void add(student** pphead)
{
	int n = 0;
	printf("请输入要录入的个数\n");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)//录入信息
	{
		student* newnode = (student*)malloc(sizeof(student));
		printf("请输入要录入的学号\n");
		scanf("%s", newnode->no);
		printf("请输入要录入的姓名\n");
		scanf("%s", newnode->name);
		printf("请输入要录入的电话号码\n");
		scanf("%s", newnode->tele);
		printf("请输入要录入的身份证号\n");
		scanf("%s", newnode->ID);
		printf("请输入要录入的籍贯\n");
		scanf("%s", newnode->jg);
		newnode->next = NULL;
		//连接入链表
		if (*pphead == NULL)//判断是否为空表
			*pphead = newnode;
		else
		{
			student* tmp = *pphead;
			while (tmp->next != NULL)
			{
				tmp = tmp->next;
			}
			tmp->next = newnode;
		}
	}
	printf("录入完成...\n");
	save_file(pphead);
	system("pause");
	system("cls");
}
void revise(student** pphead)
{
	assert(pphead);//判断指针是否有效
	char no[12] = { 0 };
	//学号查询：输出该学号学生的信息
	printf("请输入要修改的学号:>\n");
	scanf("%s", no);
	student* tmp = search(*pphead, no);
	if (tmp == NULL)
	{
		printf("找不到该学号\n");
	}
	else
	{
		printf("请输入修改后的学号:>\n");
		scanf("%s", tmp->no);
		printf("请输入修改后的姓名：\n");
		scanf("%s", tmp->name);
		printf("请输入修改后的电话号码\n");
		scanf("%s", tmp->tele);
		printf("请输入修改后的身份证号\n");
		scanf("%s", tmp->ID);
		printf("请输入修改后的籍贯\n");
		scanf("%s", tmp->jg);
		printf("修改完成\n");
	}
	save_file(pphead);//同步文件信息
	system("pause");
	system("cls");
}
void find(student* phead)
{
	int i = 0;//循环变量
	char no[12] = { 0 };
	//学号查询：输出该学号学生的信息
	printf("请输入要查询的学号:>\n");
	scanf("%s", no);
	student* tmp = search(phead, no);
	if (tmp == NULL)
	{
		printf("找不到该学号\n");
	}
	else
	{
		//输出指定内容
		printf("学号\t\t姓名\t\t电话号码\t\t身份证号码\t\t籍贯\n");
		Print(tmp);
	}
	system("pause");
	system("cls");
}

void dele(student** pphead)
{
	if (*pphead == NULL)//判断是否为空表
	{
		printf("没有数据，无法删除\n");
		system("pause");
		system("cls");
		return;
	}
	else
	{
		char no[12] = { 0 };
		printf("请输入需要删除的学号\n");
		scanf("%s", no);
		student* tmp = *pphead;
		student* temp = NULL;
		if (strcmp(tmp->no, no) == 0)
		{
			*pphead = tmp->next;
			tmp->next = NULL;
			free(tmp);
			printf("删除完成\n");
			save_file(pphead);//同步文件信息
			system("pause");
			system("cls");
			return;
		}
		while (tmp->next != NULL)
		{
			if (strcmp(tmp->next->no, no) == 0)
			{
				temp = tmp->next;
				tmp->next = tmp->next->next;
				temp->next = NULL;
				free(temp);
				printf("删除完成\n");
				save_file(pphead);//同步文件信息
				system("pause");
				system("cls");
				return;
			}
			tmp = tmp->next;
		}
		printf("找不到该学号，退出:>\n");
		save_file(pphead);//同步文件信息
		system("pause");
		system("cls");
	}
}


void print(student* phead)
{
	student* tmp = phead;
	if (phead == NULL)
	{
		printf("没有信息，无法打印\n");
	}
	else
	{
		printf("学号\t\t姓名\t\t电话号码\t\t身份证号码\t\t籍贯\n");
		while (tmp != NULL)
		{
			Print(tmp);
			tmp = tmp->next;
		}
		printf("打印完成...\n");
	}
	system("pause");
	system("cls");
}
