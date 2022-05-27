#define _CRT_SECURE_NO_WARNINGS 1

#include"system.h"

void menu()//�˵�����
{
	printf("*********************************************************\n");
	printf("************  	  У�˶������ϵͳ           ************\n");
	printf("*********************************************************\n");
	printf("************      [1]�½�������Ŀ            ************\n");
	printf("************  	  [2]��ѯ������Ϣ            ************\n");
	printf("************      [3]�޸ı�����Ϣ            ************\n");
	printf("************      [4]ɾ��������Ϣ            ************\n");
	printf("************      [5]���������Ϣ            ************\n");
	printf("************      [6]ͳ����Ŀ��ѧԺ�ɼ�����  ************\n");
	printf("************      [0]�˳�                    ************\n");
	printf("*********************************************************\n");
}

void read_file(proj** pphead)//���ļ�
{
	FILE* fp = fopen("sport.txt", "r");
	if (!fp)
		return;
	while (1)
	{
		proj* newnode = (proj*)malloc(sizeof(proj));
		if (newnode == NULL)
		{
			printf("�ļ���ȡʧ�ܣ�");
			exit(0);
		}
		else
		{
			if (fread(newnode, sizeof(proj), 1, fp) < 1)
				break;
			newnode->next = *pphead;
			*pphead = newnode;
		}
	}
	fclose(fp);
}

void save_file(proj** pphead)//�����ļ�
{
	FILE* fp = fopen("sport.txt", "w+");
	proj* tmp = *pphead;
	if (!fp)
		return;
	while (tmp)
	{
		fwrite(tmp, sizeof(proj), 1, fp);
		tmp = tmp->next;
	}
	fclose(fp);
}

void Creat(proj** pphead)//�½�������Ŀ
{
	int num = 0;//�μӱ�����ѧԺ����
	int i = 0;
	proj* newnode = (proj*)malloc(sizeof(proj));
	if (newnode == NULL)
	{
		printf("���ٿռ�ʧ�ܣ�");
		exit(0);
	}
	printf("��������Ŀ���ƣ�\n");
	//������Ϣ
	scanf("%s", newnode->project);
	printf("������μӸ���Ŀ��ѧԺ������\n");
	scanf("%d", &num);
	newnode->num = num;
	for (i = 0; i < num; i++)
	{
		printf("�������%d��ѧԺ���ƣ�\n",i+1);
		scanf("%s", newnode->name[i]);
		newnode->score[i] = 0;
		newnode->no[i] = 0;
	}
	newnode->next = NULL;
	//�������,����
	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		proj* tmp = *pphead;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = newnode;
	}
	printf("�½���Ŀ�ɹ���\n");
	save_file(pphead);//ͬ���ļ�����
	system("pause");
	system("cls");
}

static proj* search_by_proj(proj* phead, char name[])//ͨ����Ŀ�����ҵ�ָ�����
{
	assert(phead);
	proj* tmp = phead;
	while (tmp != NULL)
	{
		if (strcmp(tmp->project, name) == 0)
		{
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

static PRINT(proj* tmp)//���ָ��������Ϣ
{
	int i = 0;//ѭ������
	printf("\t��Ŀ���ƣ�%s\n", tmp->project);
	printf("ѧԺ����\t����ɼ�\t��������\n");
	for (i = 0; i < tmp->num; i++)
	{
		printf("%s\t\t%.2lf\t\t%d\n", tmp->name[i], tmp->score[i], tmp->no[i]);
	}
}

void Search(proj* phead)//��ѯ������Ϣ
{
	int i = 0;//ѭ������
	int input = 0;
	char name[40] = { 0 };
	//���ݱ�����Ŀ��ѯ������μӸ���Ŀ������ѧԺ����Ϣ
	//ѧԺ���Ʋ�ѯ�������ѧԺ�μӵ�������Ŀ��Ϣ
	while (1)
	{
		printf("�������ѯ�ķ�ʽ��\n1.��������Ŀ��ѯ\n2.��ѧԺ���Ʋ�ѯ\n");
		printf("��ѡ��:>\n");
		scanf("%d", &input);
		if (input == 1)//��������Ŀ��ѯ
		{
			printf("������Ҫ��ѯ����Ŀ����:>\n");
			scanf("%s", name);
			proj* tmp = search_by_proj(phead, name);
			if (tmp == NULL)
			{
				printf("�Ҳ�������Ŀ\n");
			}
			else
			{
				//���ָ������
				PRINT(tmp);
			}
			break;
		}
		else if (input == 2)//��ѧԺ���Ʋ�ѯ
		{
			printf("������Ҫ��ѯ��ѧԺ����:>\n");
			scanf("%s", name);
			proj* tmp = phead;
			printf("��Ŀ����\t����ɼ�\t��������\n");
			while (tmp != NULL)
			{
				for (i = 0; i < tmp->num; i++)
				{
					if (strcmp(tmp->name[i], name) == 0)
					{
						printf("%s\t%.2lf\t%d\n", tmp->project, tmp->score[i], tmp->no[i]);
					}
				}
				tmp = tmp->next;
			}
			break;
		}
		else
		{
			printf("�����������������\n");
		}
	}
	system("pause");
	system("cls");

}
void Revise(proj** pphead)//�޸ı�����Ϣ
{
	int input = 0;
	int i = 0;//ѭ������
	int num = 0;//����ѧԺ����
	char project[40] = { 0 };
	while (1)
	{
		printf("��ѡ��\n1.�޸���Ŀ\n2.�޸ķ���\n");
		scanf("%d", &input);
		if (input == 1)//�޸���Ŀ
		{
			printf("������Ҫ�޸ĵ���Ŀ����:>\n");
			scanf("%s", project);
			proj* tmp = search_by_proj(*pphead, project);
			if (tmp == NULL)
			{
				printf("�Ҳ�������Ŀ���˳�:>\n");
			}
			else
			{
				printf("�������޸ĺ����Ŀ����:>\n");
				scanf("%s", tmp->project);
				printf("������μӸ���Ŀ��ѧԺ������\n");
				scanf("%d", &num);
				tmp->num = num;
				for (i = 0; i < num; i++)
				{
					printf("�������%d��ѧԺ���ƣ�\n", i + 1);
					scanf("%s", tmp->name[i]);
					tmp->score[i] = 0;
					tmp->no[i] = 0;
				}
				printf("�޸����\n");
			}
			break;
		}
		else if (input == 2)//�޸ķ���
		{
			printf("������Ҫ�޸ĵ���Ŀ����:>\n");
			scanf("%s", project);
			proj* tmp = search_by_proj(*pphead, project);
			if (tmp == NULL)
			{
				printf("�Ҳ�������Ŀ���˳�:>\n");
			}
			else
			{
				for (i = 0; i < tmp->num; i++)
				{
					printf("������%sѧԺ�ĳɼ�", tmp->name[i]);
					scanf("%lf", &tmp->score[i]);
				}
				printf("�޸����\n");
			}
			break;
		}
		else
		{
			printf("�����������������\n");
		}
	}
	save_file(pphead);//ͬ���ļ���Ϣ
	system("pause");
	system("cls");

}
void Delete(proj** pphead)//ɾ��������Ϣ
{
	char project[40] = { 0 };
	printf("��������Ҫɾ������Ŀ����\n");
	scanf("%s", project);
	proj* tmp = *pphead;
	if (strcmp(tmp->project, project) == 0)
	{
		*pphead = tmp->next;
		free(tmp->next);
		tmp->next = NULL;
		printf("ɾ�����\n");
		save_file(pphead);//ͬ���ļ���Ϣ
		system("pause");
		system("cls");
		return;
	}
	while (tmp->next != NULL)
	{
		if (strcmp(tmp->next->project, project) == 0)
		{
			tmp->next = tmp->next->next;
			free(tmp->next);
			tmp->next = NULL;
			printf("ɾ�����\n");
			save_file(pphead);//ͬ���ļ���Ϣ
			system("pause");
			system("cls");
			return;
		}
		tmp = tmp->next;
	}
	printf("Ϊ�ҵ�����Ŀ���˳�:>\n");
	save_file(pphead);//ͬ���ļ���Ϣ
	system("pause");
	system("cls");
}
void Print(proj* phead)//���������Ϣ
{
	if (phead == NULL)
	{
		printf("û�б�����Ŀ��Ϣ���޷������\n");
	}
	else
	{
		proj* tmp = phead;
		while (tmp != NULL)
		{
			PRINT(tmp);
			tmp = tmp->next;
		}
	}
	system("pause");
	system("cls");

}

static Swap(const void* x, const void* y, unsigned int size)
{
	unsigned int i = 0;//����ѭ������
	for (i = 0; i < size; i++)
	{
		char tmp = *((char*)x + i);
		*((char*)x + i) = *((char*)y + i);
		*((char*)y + i) = tmp;
	}
}

void Stats_project(proj** pphead)//ͳ����Ŀ��ѧԺ�ɼ�����
{
	int i = 0;//ѭ������
	int j = 0;
	char project[40] = { 0 };
	printf("������Ҫͳ�Ƶ���Ŀ����:>\n");
	scanf("%s", project);
	proj* tmp = search_by_proj(*pphead, project);
	if (tmp == NULL)
	{
		printf("û���ҵ�����Ŀ���˳�:>\n");
	}
	else
	{
		for (j = 0; j < tmp->num; j++)
		{
			for (i = 0; i < tmp->num - j + 1; i++)
			{
				if (tmp->score[i] < tmp->score[i + 1])
				{
					Swap(&tmp->score[i], &tmp->score[i + 1], sizeof(tmp->score[i]));
					Swap(&tmp->name[i], &tmp->name[i + 1], sizeof(tmp->name[i]));
				}
			}
		}
		for (i = 0; i < tmp->num; i++)
		{
			tmp->no[i] = i + 1;
		}
		printf("ͳ�����\n");
	}
	save_file(pphead);//ͬ���ļ���Ϣ
	system("pause");
	system("cls");
}
