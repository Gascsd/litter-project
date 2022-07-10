#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

void menu()
{
	printf("********************************\n");
	printf("******  1.add    2.sub    ******\n");
	printf("******  3.mul    4.div    ******\n");
	printf("******  0.exit            ******\n");
	printf("********************************\n");
}

int add(int x, int y)
{
	return x + y;
}
int sub(int x, int y)
{
	return x - y;
}
int mul (int x, int y)
{
	return x * y;
}
int div(int x, int y)
{
	return x / y;
}


//int main()
//{
//	int input = 0;
//	int x = 0;
//	int y = 0;
//	int ret = 0;
//	do
//	{
//		menu();//���ò˵�����
//		printf("������Ҫ���еĲ���:>\n");
//		scanf("%d", &input);//����ѡ����
//		switch (input)
//		{
//		case 1:
//			printf("����������������:>\n");
//			scanf("%d%d", &x, &y);
//			ret = add(x, y);
//			printf("�����%d\n", ret);
//			break;
//		case 2:
//			printf("����������������:>\n");
//			scanf("%d%d", &x, &y);
//			ret = sub(x, y);
//			printf("�����%d\n", ret);
//			break;
//		case 3:
//			printf("����������������:>\n");
//			scanf("%d%d", &x, &y);
//			ret = mul(x, y);
//			printf("�����%d\n", ret);
//			break;
//		case 4:
//			printf("����������������:>\n");
//			scanf("%d%d", &x, &y);
//			ret = div(x, y);
//			printf("�����%d\n", ret);
//			break;
//		case 0:
//			printf("�˳�������\n");
//			break;
//		default:
//			printf("�����������������\n");
//		}
//	} while (input);
//	return 0;
//}



int main()
{
	int input = 0;
	int x = 0;
	int y = 0;
	int ret = 0;
	do
	{
		menu();//���ò˵�����
		printf("������Ҫ���еĲ���:>\n");
		scanf("%d", &input);//����ѡ����
		if (input > 0 && input <= 4)
		{
			printf("����������������:>\n");
			scanf("%d%d", &x, &y);
			int (*pf[5])(int, int) = { 0,add,sub,mul,div };//���庯��ָ������
			ret = pf[input](x, y);//ͨ��input��ֵ���ú���
			printf("�����%d\n", ret);
		}
		else if (input == 0)
		{
			printf("�˳�\n");
			break;
		}
		else
		{
			printf("�����������������\n");
		}
	} while (input);
	return 0;
}


