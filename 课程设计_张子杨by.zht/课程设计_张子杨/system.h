#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<Windows.h>

struct node //�����ṹ������struct node
{
    char no[12];//�豸���
    char name[40];//����
    double dj;//����
    int num;//����
    double jine;//���
    struct node* next;//ָ����һ���ڵ��ָ��
};
struct node* head;//����ָ��struct node �ṹ�������ָ�����


void menu();
void create(struct node** phead);
void search(struct node* head);
void revise(struct node** phead);
void delete(struct node** phead);
void print(struct node* head);
void count(struct node* head);
void stats(struct node* head);
