#define _CRT_SECURE_NO_WARNINGS 1

#include"system.h"

student* phead = NULL;//����ͷ�ڵ�ָ��

int main()
{
	printf("��ӭʹ��ѧ��������Ϣ����ϵͳ!\n");
	read_file(&phead);//���ļ�
	int input = 0;
	while (1)
	{
		menu();//��ӡ�˵�
		printf("��ѡ��:>\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			add(&phead);//������Ϣ
			break;
		case 2:
			revise(&phead);//�޸���Ϣ
			break;
		case 3:
			find(phead);//������Ϣ
			break;
		case 4:
			dele(&phead);//ɾ����Ϣ
			break;
		case 5:
			print(phead);//��ӡ��Ϣ
			break;
		case 0:
			printf("�˳�...\n");//�˳�
			save_file(&phead);
			return 0;
		default:
			printf("�����������������\n");
		}
	}
}
