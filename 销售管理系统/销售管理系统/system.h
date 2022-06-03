#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PEO_NUM 20    //最多销售员总人数为20 


struct Node
{
	char no[12];     //销售员代号
	char name[40];   //销售员姓名
	int  month[12];  //月份
	float sales[12];   //月份销售额
	float total;      //年度总销售额
}; 
typedef struct Node Node;  //为结构体起别名为Node


int Menu2(void);
Node Input_people(Node pe[], int m, int n); //录入销售员信息
void Name(Node pe[], int m, int n);    //查找信息
void ModifySales(Node pe[], int m, int n);      //修改信息
void Deleteinfor(Node pe[], int m, int n);     //删除信息
void StatisticsSales(Node pe[], int m, int n);  //统计总销售额
void FA(Node pe[], int m, int n);        //找出最值
