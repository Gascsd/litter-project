#define _CRT_SECURE_NO_WARNINGS 1

#include"system.h"

int Menu2(void)
{
	int item;
	system("cls");   //�������� 
	printf("�������۹���ϵͳ����ѡ����Ҫ�Ĳ���:\n\n");
	printf("\t\t1:¼������Ա����Ϣ\n");
	printf("\t\t2:����ĳ������Աĳ���µ����۶�\n");
	printf("\t\t3:�޸�ĳ������Աĳ���µ����۶�\n");
	printf("\t\t4:ɾ��ĳ������Ա��������Ϣ\n");
	printf("\t\t5:ͳ����������Ա����������۶�\n");
	printf("\t\t6:�ҳ���󣨻���С���������۶����������۶�\n");
	printf("\t\t0:�˳�\n");
	printf("\n\n����������:");
	scanf("%d", &item);    //���û�ѡ�������
	return item;
}

Node Input_people(Node pe[], int m, int n)
{
	int 	i, j;
	for (i = 0; i < m; i++)
	{
		printf("�������%iλ����Ա�Ĵ��š������������۶��������۶�\n", i + 1);
		printf("��    �ţ�");
		scanf("%s", &pe[i].no);
		getchar();                  //���˵��س���
		printf("��    ����");
		gets(pe[i].name);
		for (j = 0; j < n; j++)
		{
			printf("%d�·����۶�:", j + 1);
			scanf("%f", &pe[i].sales[j]);
		}
		pe[i].total = 0;
	}
}

void Name(Node pe[], int m, int n)
{
	char sname[15];
	int i, flag = 0, k;
	printf("������Ҫ���ҵ�����Ա����:");
	scanf("%s", sname);
	printf("������Ҫ���ҵ��·ݣ�");
	scanf("%d", &k);
	for (i = 0; i < m; i++)
	{
		if (strcmp(sname, pe[i].name) == 0)
		{
			flag = 1;
			printf("%d�·����۶�%f: ", k, pe[i].sales[k - 1]);
		}
	}
	if (flag == 0)
		printf("���޴��ˣ�\n");
}

void ModifySales(Node pe[], int m, int n)
{
	char sname[15];
	int i, q = 0, k;
	float s;
	printf("����������Ա����:");
	scanf("%s", sname);
	printf("�������·ݣ�");
	scanf("%d", &k);
	for (i = 0; i < m; i++)
	{
		if (strcmp(sname, pe[i].name) == 0)
		{
			q = 1;
			printf("������Ҫ�޸ĵ���ֵ:");
			scanf("%f", &s);
			pe[i].sales[k - 1] = s;
			break;
		}
	}
	if (q == 0)
		printf("���޴��ˣ�\n");

}


void Deleteinfor(Node pe[], int m, int n)
{
	char sname[15];
	int i, j, q, x;
	printf("������Ҫɾ����Ϣ������Ա����:");
	scanf("%s", sname);
	for (i = 0; i < m; i++)
	{
		if (strcmp(sname, pe[i].name) == 0)
		{
			q = 1;
			for (j = i; j < (m - 1); j++)
			{
				strcpy(pe[j].name, pe[j + 1].name);
				for (x = 0; x < n; x++)
				{
					pe[j].sales[x] = pe[j + 1].sales[x - 1];
				}
			}
		}
	}
	//pe[m - 1] = ;
	if (q == 0)
	{
		printf("���޴��ˣ�\n");
	}
	printf("ɾ���ɹ���");
}


void StatisticsSales(Node pe[], int m, int n)
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			pe[i].total += pe[i].sales[j];
		}
	}
	for (i = 0; i < m; i++)
	{
		printf("��    ����%s ,�����۶�: %f", pe[i].name, pe[i].total);
		printf("\n");
	}

}

void FA(Node pe[], int m, int n)
{
	int i, j;
	float min1 = pe[0].sales[0];	//min1��max1�ֱ�Ϊ�����۶����ֵ����Сֵ
	float max1 = pe[0].sales[0];	//�ֽ���һ���˵ĵ�һ�µ����۶���Ϊ��Сֵ�����ֵ 
	int num1 = 0, num2 = 0, month1 = 0, month2 = 0, num3 = 0, num4 = 0;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (min1 > pe[i].sales[j])
			{
				min1 = pe[i].sales[j];
				num1 = i;       //�������� 
				month1 = j;     //�����·� 
			}
			if (max1 < pe[i].sales[j])
			{
				max1 = pe[i].sales[j];
				num2 = i;
				month2 = j;
			}
			pe[i].total += pe[i].sales[j];   //������������۶� 
		}

	}

	float min2 = pe[0].total;  //min2��max2�ֱ�����������۶����ֵ����Сֵ 
	float max2 = pe[0].total;
	for (i = 0; i < m; i++)
	{
		if (min2 > pe[i].total)
		{
			min2 = pe[i].total;
			num3 = i;
		}
		if (max2 < pe[i].total)
		{
			max2 = pe[i].total;
			num4 = i;
		}
	}
	printf("%s ��%d�����۶���СΪ%f��\n", pe[num1].name, month1 + 1, min1);
	printf("%s ��%d�����۶����Ϊ%f:\n", pe[num2].name, month2 + 1, max1);
	printf("%s ����������۶���СΪ%f��\n", pe[num3].name, min2);
	printf("%s ����������۶����Ϊ%f��\n", pe[num4].name, max2);
}

