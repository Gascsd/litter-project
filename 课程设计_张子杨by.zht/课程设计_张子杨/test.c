#define _CRT_SECURE_NO_WARNINGS 1

#include"system.h"

int main()
{
    struct node*  head = NULL;//����ָ��struct node �ṹ�������ָ�����
    int pw = 123;
    int paw = 0;
    while (1)
    {
        printf("�������¼���룺\n");
        scanf("%d", &paw);
        if (paw == pw)
        {
            printf("������ȷ\n");
            while (1)
            {
                int n;
                menu();
                printf("������:>\n");
                scanf("%d", &n);
                switch (n)
                {
                case 0:
                    printf("�˳�:>\n");
                    return 0;
                    //break;
                case 1:
                    create(&head);//����������,������Ϣ
                    break;
                case 2:
                    search(head);//������Ϣ 
                    break;
                case 3:
                    revise(&head);//�޸Ĺ����
                    break;
                case 4:
                    delete(&head);//ɾ�������
                    break;
                case 5:
                    print(head);//��ӡ��Ϣ
                    break;
                case 6:
                    count(head);//����ÿ���豸���
                    break;
                case 7:
                    stats(head);//ͳ���豸���������ܽ��
                    break;
                default:
                    printf("�����������������\n");
                    break;
                }
            }
        }
        else
        {
            printf("���������ѡ�����в���>\n");
            printf("������0�˳�����������������������������\n");
            int input = 0;
            scanf("%d", &input);
            if (input == 0)
                return 0;
        }
    }
    return 0;
}
