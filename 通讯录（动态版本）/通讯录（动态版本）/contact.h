#pragma once

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>

#define DEFAULT_SZ 3
#define INC_SZ 2

typedef struct PeoInfo
{
	char name[20];
	char sexy[10];
	int age;
	char tele[12];
	char addr[30];
}PeoInfo;


typedef struct Contact
{
	PeoInfo* data;
	int count;//存入的数据个数
	int capacity;//通讯录容量
}Contact;



void menu();
void ContactInit(Contact* pc);
void ContactAdd(Contact* pc);
void ContactDel(Contact* pc);
void ContactSearch(const Contact* pc);
void ContactModify(Contact* pc);
void ContactShow(const Contact* pc);
void ContactSort(Contact* pc);
void ContactDestroy(Contact* pc);


