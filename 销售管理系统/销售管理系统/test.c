#define _CRT_SECURE_NO_WARNINGS 1

#include "system.h"

int main()
{
	Node pe[PEO_NUM];
	int m, n = 12;     //mΪʵ������Ա������nΪ�·ݣ���Ϊ12 
	int item;
	printf("����������Ա������:");
	scanf("%d", &m);
	while (1)
	{
		item = Menu2();     //�˵���ʾ,��ȡ�û�ѡ���ѡ��
		switch (item)
		{
		case 1:
			Input_people(pe, m, n);  //¼����Ϣ
			getchar();
			getchar();
			break;
		case 2:
			Name(pe, m, n); 	//������Ϣ
			getchar();
			break;
		case 3:
			ModifySales(pe, m, n);   //�޸���Ϣ
			getchar();
			break;
		case 4:
			Deleteinfor(pe, m, n);  //ɾ����Ϣ
			getchar();
			break;
		case 5:
			StatisticsSales(pe, m, n); //ͳ�������۶�
			getchar();
			break;
		case 6:
			FA(pe, m, n);         //�ҳ���ֵ
			getchar();
			break;
		case 0:
			exit(0);             //�˳� 
			printf("�������\n");
			getchar();
			break;
		default:
			printf("\n\n����������ȷ������������!\n");
			getchar();
			break;
		}
	}
}