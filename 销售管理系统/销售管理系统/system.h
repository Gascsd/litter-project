#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PEO_NUM 20    //�������Ա������Ϊ20 


struct Node
{
	char no[12];     //����Ա����
	char name[40];   //����Ա����
	int  month[12];  //�·�
	float sales[12];   //�·����۶�
	float total;      //��������۶�
}; 
typedef struct Node Node;  //Ϊ�ṹ�������ΪNode


int Menu2(void);
Node Input_people(Node pe[], int m, int n); //¼������Ա��Ϣ
void Name(Node pe[], int m, int n);    //������Ϣ
void ModifySales(Node pe[], int m, int n);      //�޸���Ϣ
void Deleteinfor(Node pe[], int m, int n);     //ɾ����Ϣ
void StatisticsSales(Node pe[], int m, int n);  //ͳ�������۶�
void FA(Node pe[], int m, int n);        //�ҳ���ֵ
