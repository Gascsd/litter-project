#define _CRT_SECURE_NO_WARNINGS 1

#include"contact.h"


//ʵ��һ��ͨѶ¼��
//ͨѶ¼���������洢1000���˵���Ϣ��ÿ���˵���Ϣ�������������Ա����䡢�绰��סַ
//�ṩ������
//1.�����ϵ����Ϣ
//2.ɾ��ָ����ϵ����Ϣ
//3.����ָ����ϵ����Ϣ
//4.�޸�ָ����ϵ����Ϣ
//5.��ʾ������ϵ����Ϣ
//6.���������ϵ��
//7.����������������ϵ��
int main()
{
	Contact con;
	ContactInit(&con);
	int input = 0;
	do
	{
		menu();
		printf("������:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			ContactAdd(&con);
			break;
		case 2:
			ContactDel(&con);
			break;
		case 3:
			ContactSearch(&con);
			break;
		case 4:
			ContactModify(&con);
			break;
		case 5:
			ContactShow(&con);
			break;
		case 6:
			ContactDestroy(&con);
			ContactInit(&con);
			break;
		case 7:
			ContactSort(&con);
			break;
		case 0:
			printf("�˳�\n");
			break;
		default:
			printf("�����������������...\n");
		}
	} while (input);
	return 0;
}
