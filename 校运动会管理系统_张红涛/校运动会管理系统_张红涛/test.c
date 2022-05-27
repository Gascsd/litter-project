#define _CRT_SECURE_NO_WARNINGS 1

#include"system.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define LED sizeof(struct node)


struct node
{
	char xiangmu[40];
	char name[10][40];
	float score[10];
	int no[10];
	struct node* link;
};
struct node* head = NULL;


void ReadFile()
{
	FILE* f = fopen("sports.txt", "r");
	if (!f)//��ԶΪ��
		return;
	while (1)
	{
		struct node* temp = NULL;
		struct node* nd = (struct node*)malloc(LED);
		if (nd == NULL)
		{
			exit(-1);
		}
		else
		{
			if (fread(nd, LED, 1, f) < 1)
			{
				break;
			}
			temp = head;
			nd->link = NULL;
			head = nd;
			nd->link = temp;
		}
	}
	fclose(f);
}
void SaveFile()
{
	struct node* temp = NULL;
	FILE* f = fopen("sports.txt", "w+");
	if (!f)
		return;
	temp = head;
	while (temp)
	{
		fwrite(temp, LED, 1, f);
		temp = temp->link;
	}

	fclose(f);
}


/*
����ͷ�巨
*/
void in()
{
	//�������Ŀ��ѧԺ����
	int m = 0;
	int a = 0;
	struct node* p = NULL;
	struct node* q = NULL;
	p = (struct node*)malloc(LED);
	if (p == NULL)
	{
		exit(-1);
	}
	q = head;
	memset(p->no, -1, sizeof(p->no));
	p->link = NULL;
	head = p;
	p->link = q;

	printf("�������˶�����Ŀ����:\n");
	scanf("%s", p->xiangmu);
	printf("������������Ŀ��ѧԺ����:\n");
	scanf("%d", &m);
	for (a = 0; a < m; a++)
	{
		printf("�������%d��ѧԺ����:\n", a + 1);
		scanf("%s", p->name[a]);
		printf("��������˶���Ŀ�ɼ�:\n");
		scanf("%f", &p->score[a]);
		p->no[a] = 0;
	}
	printf("�����˶���Ϣ�������!\n");

}
//�鿴ĳ���˶����
void find()
{
	int i = 0;
	struct node* q = NULL;
	char name[40] = { 0 };
	printf("�������˶�����:\n");
	scanf("%s", name);
	q = head;
	while (q)
	{
		//�ҵ���Ӧ���˶�
		if (strcmp(q->xiangmu, name) == 0)
		{
			//��ʾ����ѧԺ�������Ŀ���
			for (i = 0; i < 10; i++)
			{
				if (q->no[i] == -1)
					break;
				printf("ѧԺ����:%s����Ŀ����:%.2f\n", q->name[i], q->score[i]);
			}
			return;
		}
		q = q->link;
	}
	printf("û���ҵ���Ӧ���˶���Ŀ\n");
}
void xg()
{
	int a = 0;
	int b = 0;
	struct node* q = NULL;
	char Nname[40] = { 0 };
	printf("������Ҫ�޸ĵ��˶�����:\n");
	scanf("%s", Nname);
	q = head;
	while (q)
	{
		if (strcmp(q->xiangmu, Nname) == 0)
		{
			//�޸���Ŀ��Ϣ
			printf("������������Ŀ��ѧԺ����:\n");
			scanf("%d", &a);
			memset(q->no, -1, sizeof(q->no));
			for (b = 0; b < a; b++)
			{
				printf("�������%d��ѧԺ����:\n", b + 1);
				scanf("%s", q->name[b]);
				printf("��������˶���Ŀ�ɼ�:\n");
				scanf("%f", &q->score[b]);
				q->no[b] = 0;
			}
			return;
		}
		q = q->link;
	}
}
void del()
{
	struct node* temp = NULL;
	struct node* prev = NULL;
	char sport_name[40] = { 0 };
	printf("������Ҫɾ�����˶�����:\n");
	scanf("%s", sport_name);
	temp = head;
	prev = NULL;
	while (temp)
	{
		//���б���ɾ���˶���Ŀ
		if (strcmp(sport_name, temp->xiangmu) == 0)
		{
			if (prev)
			{
				prev->link = temp->link;
			}
			else
			{
				head = temp->link;
			}
			printf("ɾ����Ŀ%s�ɹ���\n", sport_name);
			free(temp);
			return;
		}
		prev = temp;
		temp = temp->link;
	}
	printf("û���ҵ���Ӧ���˶���Ŀ!\n");
}

//�ܳɼ�����
void zpm()
{
	int i = 0, j = 0;
	int found = 0;
	int name_index = 0;
	char tn[40] = { 0 };
	char name[10][40] = { 0 };
	float total_score[10] = { 0 };
	struct node* temp = head;
	while (temp)
	{
		for (i = 0; i < 10; i++)
		{
			if (temp->no[i] == -1)//�ж��Ƿ���ѧԺ�μ������˶�
				break;

			for (j = 0; j < 10; j++)
			{
				if (strlen(name[j]) < 1)//�ж��Ƿ���ѧԺ�μ������˶�
				{
					name_index = j;
					break;
				}
				if (strcmp(name[j], temp->name[i]) == 0)
				{
					name_index = j;
					found = 1;
					break;
				}
			}
			if (found == 0)
			{
				strcpy(name[name_index], temp->name[i]);
			}
			found = 0;
			total_score[name_index] = total_score[name_index] + temp->score[i];
		}
		temp = temp->link;
	}

	//����
	for (i = 0; i < 10; i++)
	{
		for (j = i; j < 10; j++)
		{
			if (total_score[i] < total_score[j])
			{
				float t = total_score[i];
				total_score[i] = total_score[j];
				total_score[j] = t;
				strcpy(tn, name[i]);
				strcpy(name[i], name[j]);
				strcpy(name[j], tn);
			}

		}
	}
	printf("�˶����ܳɼ�����:\n");
	for (i = 0; i < 10; i++)
	{
		if (total_score[i] == 0)
			break;
		printf("��%d��:%s,�ܷ�:%.2f\n", i + 1, name[i], total_score[i]);
	}
}
//ÿ����ĿѧԺ����
void dpm()
{
	char tn[40] = { 0 };
	char name[10][40] = { 0 };
	float total_score[10] = { 0 };
	struct node* temp = NULL;
	int i = 0;
	int j = 0;
	temp = head;
	printf("�˶��ᵥ���˶�����\n");
	while (temp)
	{
		for (i = 0; i < 10; i++)
		{
			total_score[i] = -1;
		}
		//��ʱ��ֵ
		for (i = 0; i < 10; i++)
		{
			if (temp->no[i] == -1)
				break;
			strcpy(name[i], temp->name[i]);
			total_score[i] = temp->score[i];
		}
		//����
		for (i = 0; i < 10; i++)
		{
			for (j = i; j < 10; j++)
			{
				if (total_score[i] < total_score[j])
				{
					float ts = total_score[i];
					total_score[i] = total_score[j];
					total_score[j] = ts;
					strcpy(tn, name[i]);
					strcpy(name[i], name[j]);
					strcpy(name[j], tn);
				}
			}
		}
		printf("�˶�����Ŀ %s ����:\n", temp->xiangmu);		//��ʾ����Ŀ����
		for (i = 0; i < 10; i++)
		{
			if (total_score[i] < 0)
				break;
			printf("��%d��:%s������%.2f\n", i + 1, name[i], total_score[i]);
		}
		printf("\n");
		temp = temp->link;
	}
}
void Menu()
{
	//���ع��ܣ�ͬ���ļ�����
	system("cls");
	printf("\nУ�˶�����Ŀ����ϵͳ����������Ҫִ�еĵĲ�����\n\n");
	printf("\t\t|--------------У�˻���Ŀ����ϵͳ-------------|\n");
	printf("\t\t|1.¼���˶�����Ŀ�������Ϣ                   |\n");
	printf("\t\t|2.����ĳ����Ŀ����Ϣ                         |\n");
	printf("\t\t|3.�޸�ĳ����Ŀ����Ϣ                         |\n");
	printf("\t\t|4.ɾ��ĳ����Ŀ����Ϣ                         |\n");
	printf("\t\t|5.ѧԺ����ɼ�����                           |\n");
	printf("\t\t|6.ѧԺ���ܳɼ�����                           |\n");
	printf("\t\t|0.�˳�ϵͳ                                   |\n");
	printf("\t\t|---------------------------------------------|\n");
	printf("����������Ҫִ�еĹ��ܶ�Ӧ������0-6��\n");
	system("pause");
}
void one()
{
	int a, b, c, d, e;
	for (a = 6;; a++)
	{
		b = (a - 1) / 5 * 4;  //a��A�������㣬 ����a-1����5���ٳ���4������B�����������㡣��ͬ 
		c = (b - 1) / 5 * 4;
		d = (c - 1) / 5 * 4;
		e = (d - 1) / 5 * 4;
		if (a % 5 == 1 && b % 5 == 1 && c % 5 == 1 && d % 5 == 1 && e % 5 == 1)
		{
			printf("�������ٺϻﲶ�� %d ���㡣\n", a);
			break;//�˴������������������С��ֵ�������������ѭ��
		}
	}
}
void two()
{
	double x, y, pi;//x,y������������֣�pi����Բ����
	int n, s;//n������뾶Ϊһ���ķ�֮һԲ�ڵĵ�����s���ܹ���������ĵ�����
	n = s = 0;
	while (s <= 10000000)
	{
		x = rand() / 32767.0;//rand()�ǲ�����������ĺ����ٳ���32767.0�õ��������Ǵ���0-1֮����������
		y = rand() / 32767.0;//ͬ��
		if ((x * x + y * y) <= 1)
			n++;//if���ͳ�Ƴ���1/4Բ�ڵĵ�
		s++;//ͳ���ܹ��ĵ���
	}
	pi = (4.0 * n) / 10000000;//��Ϊn/s=1/4Բ�����/�߳�Ϊһ�������ε������pi/4=n/s ->pi=(4*n)/s
	printf("Բ����Լ����%1f\n", pi);
}
void three()
{
	double r = 1, n, x = 0.5;//���������������ֱ��������棬������εı�������һ��������Σ��������Σ��İ뾶��һ�� ,r�ǰ뾶Ϊһ�ĵ�λԲ��pi��Ҫ���Բ����
	for (n = 6; x > 1e-15; n *= 2)//1e-15�������10^-15�η���Ҳ����0.000000000000001��ȷ��x����Чֵ��double�ľ��ȷ�Χ�� 
	{
		x = hypot(x, 1 - sqrt(1 - x * x)) / 2;//hypotΪ��ֱ��������б�ߵĺ���(��ֱ��������б�ߵĺ���),��xΪ�������α߳���һ�룬��ôx������һ����N���εı߳���1/2
	}////����ʡ���ˣ���Ϊpai=c/d ->pai=2*x*i/2*1 ->pai=x*i ��.15��ʾ����С�����15λ 
	printf("%.15f\n ", x * n);
	printf("%.15f\n", 1e-15);
}
void nMenu()
{
	system("cls");
	printf("1.����ͷ��� 2.�������PI 3.���������PI 4.У�˶�����Ŀ���� 5.�˳�\n");

}
void Sports()
{
	char menu = 0;
	ReadFile();
	while (1)
	{
		Menu();
		menu = getchar();
		switch (menu)
		{
		case '1':
			in();
			SaveFile();
			break;
		case '2':
			find();
			break;
		case '3':
			xg();
			break;
		case '4':
			del();
			SaveFile();
			break;
		case '5':
			dpm();
			break;
		case '6':
			zpm();
			break;
		case '0':
			exit(0);
			return;
		case '\n':
			system("cls");
			continue;
		default:
			printf("�����������������\n");
			break;
		}
		system("pause");
		system("cls");
	}
}
int main()
{
	char pmenu = 0;
	int item = 0;
	while (1)
	{
		nMenu();
		pmenu = getchar();
		switch (pmenu)
		{
		case '1':
			one();
			break;
		case '2':
			two();
			break;
		case '3':
			three();
			break;
		case '4':
			Sports();
			break;
		case '5':
			return 0;
		case '\n':
			//system("cls");
			item = 1;
			break;
		default:
			printf("�����������������\n");
			break;
		}
		if (item == 0)
		{
			system("pause");
			system("cls");
		}
		else
		{
			item = 0;
		}
	}

	return 0;
}
