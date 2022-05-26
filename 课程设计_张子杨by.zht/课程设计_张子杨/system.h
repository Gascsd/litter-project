#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<Windows.h>

struct node //声明结构体类型struct node
{
    char no[12];//设备编号
    char name[40];//名称
    double dj;//单价
    int num;//数量
    double jine;//金额
    struct node* next;//指向下一个节点的指针
};
struct node* head;//定义指向struct node 结构体变量的指针变量


void menu();
void create(struct node** phead);
void search(struct node* head);
void revise(struct node** phead);
void delete(struct node** phead);
void print(struct node* head);
void count(struct node* head);
void stats(struct node* head);
