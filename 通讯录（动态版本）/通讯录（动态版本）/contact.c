#define _CRT_SECURE_NO_WARNINGS 1

#include"contact.h"


void menu()
{
	printf("************************************\n");
	printf("****** 1. add      2. del    *******\n");
	printf("****** 3. search   4. modify *******\n");
	printf("****** 5. show     6. destroy*******\n");
	printf("****** 7. sort     0. exit   *******\n");
	printf("************************************\n");
}



void ContactInit(Contact* pc)
{
	assert(pc);
	pc->data = calloc(DEFAULT_SZ, sizeof(PeoInfo));
	if (pc->data == NULL)
	{
		printf("ContactInit::%s", strerror(errno));
		exit(-1);
	}
	pc->count = 0;
	pc->capacity = DEFAULT_SZ;
}

void CheckCapacity(Contact* pc)
{
	if (pc->count == pc->capacity)
	{
		//����
		PeoInfo* ptr = (PeoInfo*)realloc(pc->data, (pc->capacity + INC_SZ) * sizeof(PeoInfo));
		if (ptr == NULL)
		{
			printf("ContactAdd::%s\n", strerror(errno));
			exit(-1);
		}
		pc->data = ptr;
		pc->capacity += INC_SZ;
		printf("���ݳɹ�\n");
	} 
}

void ContactAdd(Contact* pc)
{
	assert(pc);
	CheckCapacity(pc);
	printf("������������");
	scanf("%s", pc->data[pc->count].name);
	printf("�������Ա�");
	scanf("%s", pc->data[pc->count].sexy);
	printf("���������䣺");
	scanf("%d", &pc->data[pc->count].age);
	printf("������绰��");
	scanf("%s", pc->data[pc->count].tele);
	printf("�������ַ��");
	scanf("%s", pc->data[pc->count].addr);
	pc->count++;
	printf("����ɹ�\n");
}

int FindByName(const Contact* pc, char* name)
{
	int i = 0;
	int ret = -1;
	for (i = 0; i < pc->count; i++)
	{
		ret = strcmp(pc->data[i].name, name);
		if (ret == 0)
			return i;
	}
	return -1;
}

void ContactDel(Contact* pc)
{
	assert(pc);
	char name[20] = { 0 };
	int i = 0;
	printf("������Ҫɾ�������ƣ�");
	scanf("%s", name);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("û�ҵ������ݣ��޷�ɾ��\n");
		return;
	}
	else
	{
		for (i = pos; i < pc->count - 1; i++)
		{
			pc->data[i] = pc->data[i + 1];
		}
		pc->count--;
		printf("ɾ���ɹ�\n");
	}
}

void ContactSearch(const Contact* pc)
{
	assert(pc);
	char name[20] = { 0 };
	int i = 0;
	printf("������Ҫ���ҵ����ƣ�");
	scanf("%s", name);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("û�ҵ�������\n");
		return;
	}
	else
	{
		printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\n", "����", "�Ա�", "����", "�绰", "��ַ");
		printf("%-8s\t", pc->data[pos].name);
		printf("%-8s\t", pc->data[pos].sexy);
		printf("%-8d\t", pc->data[pos].age);
		printf("%-8s\t", pc->data[pos].tele);
		printf("%-8s\t", pc->data[pos].addr);
		printf("\n");
	}
}

void ContactModify(Contact* pc)
{
	assert(pc);
	char name[20] = { 0 };
	int i = 0;
	printf("������Ҫ�޸ĵ����ƣ�");
	scanf("%s", name);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("û�ҵ������ݣ��޷��޸�\n");
		return;
	}
	else
	{
		printf("������������");
		scanf("%s", pc->data[pos].name);
		printf("�������Ա�");
		scanf("%s", pc->data[pos].sexy);
		printf("���������䣺");
		scanf("%d", &pc->data[pos].age);
		printf("������绰��");
		scanf("%s", pc->data[pos].tele);
		printf("�������ַ��");
		scanf("%s", pc->data[pos].addr);
		printf("�޸ĳɹ�\n");
	}
}


void ContactShow(const Contact* pc)
{
	assert(pc);
	int i = 0;
	if (pc->count == 0)
	{
		printf("ͨѶ¼��û����Ϣ���޷���ʾ\n");
		return;
	}
	printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\n","����","�Ա�","����","�绰","��ַ");
	for (i = 0; i < pc->count; i++)
	{
		printf("%-8s\t", pc->data[i].name);
		printf("%-8s\t", pc->data[i].sexy);
		printf("%-8d\t", pc->data[i].age);
		printf("%-8s\t", pc->data[i].tele);
		printf("%-8s\t", pc->data[i].addr);
		printf("\n");
	}
}


void ContactDestroy(Contact* pc)
{
	assert(pc);
	free(pc->data);
	pc->data = NULL;
	printf("���ٳɹ�\n");
}


int cmp_by_name(const void* e1,const void* e2)
{
	return strcmp(((PeoInfo*)e1)->name, ((PeoInfo*)e2)->name);
}
void ContactSort(Contact* pc)
{
	assert(pc);
	qsort(pc->data, pc->count, sizeof(PeoInfo), cmp_by_name);
	printf("����ɹ�\n");
}
