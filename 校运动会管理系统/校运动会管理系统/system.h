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


typedef struct account//�����˺Žṹ��
{
	char UserName;//�˺�
	char Password;//����
	int permission;//Ȩ�� 1 2 3 4
}account;


typedef struct node
{
	char project[40];//������Ŀ����
	int num;//����ѧԺ����
	char name[10][40];//����ѧԺ����
	double score[10];//����ɼ�
	int no[10];//��������
	struct node* next;//ָ����һ�ڵ��ָ��
}proj;


void read_file(proj** pphead);//���ļ�
void save_file(proj** pphead);//�����ļ�
void menu();//�˵�����
void Creat(proj** pphead);//�½�������Ŀ
void Search(proj* phead);//��ѯ������Ϣ
void Revise(proj** pphead);//�޸ı�����Ϣ
void Delete(proj** pphead);//ɾ��������Ϣ
void Print(proj* phead);//���������Ϣ
void Stats_project(proj** pphead);//ͳ����Ŀ��ѧԺ�ɼ�����
void Stats_academy(proj* phead);//ͳ�Ƹ�ѧԺ�ܳɼ�������

