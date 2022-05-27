#pragma once

#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<malloc.h>
#include<assert.h>

enum
{
	Exit,
	creat,
	search,
	revise,
	delete,
	print,
	stats_project,
};


typedef struct account//定义账号结构体
{
	char UserName;//账号
	char Password;//密码
	int permission;//权限 1 2 3 4
}account;


typedef struct node
{
	char project[40];//比赛项目名称
	int num;//参赛学院个数
	char name[10][40];//参赛学院名称
	double score[10];//单项成绩
	int no[10];//单项名次
	struct node* next;//指向下一节点的指针
}proj;


void read_file(proj** pphead);//读文件
void save_file(proj** pphead);//保存文件
void menu();//菜单函数
void Creat(proj** pphead);//新建比赛项目
void Search(proj* phead);//查询比赛信息
void Revise(proj** pphead);//修改比赛信息
void Delete(proj** pphead);//删除比赛信息
void Print(proj* phead);//输出比赛信息
void Stats_project(proj** pphead);//统计项目内学院成绩排名
void Stats_academy(proj* phead);//统计各学院总成绩和排名

