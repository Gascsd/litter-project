#include "System.h"

void Test()
{
    int input = 0;
    do
    {
        printf("��ѡ���Ƿ����ϵͳ��\n0.�˳�    1.����ϵͳ\n");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            printf("����ϵͳ......\n");
            System();
            break;
        case 0:
            printf("�˳�ϵͳ\n");
            break;
        default:
            printf("����Ƿ�������������\n");
        }
    } while (input);
}

int main()
{
    Test_save();
    return 0;
}
