#pragma once

#include"stdio.h" 
#include"stdlib.h" 
#include<assert.h>
#include<Windows.h>

typedef struct student
{
    char no[12];   		//学号
    char name[40]; 		//姓名
    char tele[20]; 		//电话号码
    char  ID[20];       //身份证号码
    char jg[60];   		//籍贯
    struct student* next;	//指向下一结点的指针
}student;


void read_file(student** pphead);//读文件
void save_file(student** pphead);//保存文件
void menu();
void add(student** pphead);
void revise(student** pphead);
void find(student* phead);
void dele(student** pphead);
void print(student* phead);
