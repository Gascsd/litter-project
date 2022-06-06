#define _CRT_SECURE_NO_WARNINGS 1

#include"system.h"

void read_file(student** pphead)//���ļ�
{
	assert(pphead);
	FILE* fp = fopen("data.txt", "r");
	if (!fp)
		return;
	while (1)
	{
		student* newnode = (student*)malloc(sizeof(student));
		if (newnode == NULL)
		{
			printf("�ļ���ȡʧ�ܣ�");
			exit(0);
		}
		else
		{
			if (fread(newnode, sizeof(student), 1, fp) < 1)
				break;
			newnode->next = *pphead;
			*pphead = newnode;
		}
	}
	fclose(fp);
}

void save_file(student** pphead)//�����ļ�
{
	assert(pphead);
	FILE* fp = fopen("data.txt", "w+");
	student* tmp = *pphead;
	if (!fp)
		return;
	while (tmp)
	{
		fwrite(tmp, sizeof(student), 1, fp);
		tmp = tmp->next;
	}
	fclose(fp);
}

static Print(student* tmp)//���ָ������
{
	printf("%s\t%s\t\t%s\t\t%s\t%s\n", tmp->no, tmp->name, tmp->tele, tmp->ID, tmp->jg);
}

static student* search(student* phead, char no[])//ͨ��ѧ���ҵ�ָ�����
{
	assert(phead);
	student* tmp = phead;
	while (tmp != NULL)
	{
		if (strcmp(tmp->no, no) == 0)
		{
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

void menu()//��ӡ�˵�
{
	printf("****************************************\n");
	printf("********** ѧ���������ϵͳ ************\n");
	printf("****************************************\n");
	printf("**********  1.����ѧ����Ϣ  ************\n");
	printf("**********  2.�޸�ѧ����Ϣ  ************\n");
	printf("**********  3.����ѧ����Ϣ  ************\n");
	printf("**********  4.ɾ��ѧ����Ϣ  ************\n");
	printf("**********  5.��ӡѧ����Ϣ  ************\n");
	printf("**********  0.�˳�          ************\n");
	printf("****************************************\n");
}

void add(student** pphead)
{
	int n = 0;
	printf("������Ҫ¼��ĸ���\n");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)//¼����Ϣ
	{
		student* newnode = (student*)malloc(sizeof(student));
		printf("������Ҫ¼���ѧ��\n");
		scanf("%s", newnode->no);
		printf("������Ҫ¼�������\n");
		scanf("%s", newnode->name);
		printf("������Ҫ¼��ĵ绰����\n");
		scanf("%s", newnode->tele);
		printf("������Ҫ¼������֤��\n");
		scanf("%s", newnode->ID);
		printf("������Ҫ¼��ļ���\n");
		scanf("%s", newnode->jg);
		newnode->next = NULL;
		//����������
		if (*pphead == NULL)//�ж��Ƿ�Ϊ�ձ�
			*pphead = newnode;
		else
		{
			student* tmp = *pphead;
			while (tmp->next != NULL)
			{
				tmp = tmp->next;
			}
			tmp->next = newnode;
		}
	}
	printf("¼�����...\n");
	save_file(pphead);
	system("pause");
	system("cls");
}
void revise(student** pphead)
{
	assert(pphead);//�ж�ָ���Ƿ���Ч
	char no[12] = { 0 };
	//ѧ�Ų�ѯ�������ѧ��ѧ������Ϣ
	printf("������Ҫ�޸ĵ�ѧ��:>\n");
	scanf("%s", no);
	student* tmp = search(*pphead, no);
	if (tmp == NULL)
	{
		printf("�Ҳ�����ѧ��\n");
	}
	else
	{
		printf("�������޸ĺ��ѧ��:>\n");
		scanf("%s", tmp->no);
		printf("�������޸ĺ��������\n");
		scanf("%s", tmp->name);
		printf("�������޸ĺ�ĵ绰����\n");
		scanf("%s", tmp->tele);
		printf("�������޸ĺ�����֤��\n");
		scanf("%s", tmp->ID);
		printf("�������޸ĺ�ļ���\n");
		scanf("%s", tmp->jg);
		printf("�޸����\n");
	}
	save_file(pphead);//ͬ���ļ���Ϣ
	system("pause");
	system("cls");
}
void find(student* phead)
{
	int i = 0;//ѭ������
	char no[12] = { 0 };
	//ѧ�Ų�ѯ�������ѧ��ѧ������Ϣ
	printf("������Ҫ��ѯ��ѧ��:>\n");
	scanf("%s", no);
	student* tmp = search(phead, no);
	if (tmp == NULL)
	{
		printf("�Ҳ�����ѧ��\n");
	}
	else
	{
		//���ָ������
		printf("ѧ��\t\t����\t\t�绰����\t\t���֤����\t\t����\n");
		Print(tmp);
	}
	system("pause");
	system("cls");
}

void dele(student** pphead)
{
	if (*pphead == NULL)//�ж��Ƿ�Ϊ�ձ�
	{
		printf("û�����ݣ��޷�ɾ��\n");
		system("pause");
		system("cls");
		return;
	}
	else
	{
		char no[12] = { 0 };
		printf("��������Ҫɾ����ѧ��\n");
		scanf("%s", no);
		student* tmp = *pphead;
		student* temp = NULL;
		if (strcmp(tmp->no, no) == 0)
		{
			*pphead = tmp->next;
			tmp->next = NULL;
			free(tmp);
			printf("ɾ�����\n");
			save_file(pphead);//ͬ���ļ���Ϣ
			system("pause");
			system("cls");
			return;
		}
		while (tmp->next != NULL)
		{
			if (strcmp(tmp->next->no, no) == 0)
			{
				temp = tmp->next;
				tmp->next = tmp->next->next;
				temp->next = NULL;
				free(temp);
				printf("ɾ�����\n");
				save_file(pphead);//ͬ���ļ���Ϣ
				system("pause");
				system("cls");
				return;
			}
			tmp = tmp->next;
		}
		printf("�Ҳ�����ѧ�ţ��˳�:>\n");
		save_file(pphead);//ͬ���ļ���Ϣ
		system("pause");
		system("cls");
	}
}


void print(student* phead)
{
	student* tmp = phead;
	if (phead == NULL)
	{
		printf("û����Ϣ���޷���ӡ\n");
	}
	else
	{
		printf("ѧ��\t\t����\t\t�绰����\t\t���֤����\t\t����\n");
		while (tmp != NULL)
		{
			Print(tmp);
			tmp = tmp->next;
		}
		printf("��ӡ���...\n");
	}
	system("pause");
	system("cls");
}
