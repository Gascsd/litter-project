#pragma once

#include"stdio.h" 
#include"stdlib.h" 
#include<assert.h>
#include<Windows.h>

typedef struct student
{
    char no[12];   		//ѧ��
    char name[40]; 		//����
    char tele[20]; 		//�绰����
    char  ID[20];       //���֤����
    char jg[60];   		//����
    struct student* next;	//ָ����һ����ָ��
}student;


void read_file(student** pphead);//���ļ�
void save_file(student** pphead);//�����ļ�
void menu();
void add(student** pphead);
void revise(student** pphead);
void find(student* phead);
void dele(student** pphead);
void print(student* phead);
