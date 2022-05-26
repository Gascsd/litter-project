#define _CRT_SECURE_NO_WARNINGS 1

#include"system.h"

int main()
{
    struct node*  head = NULL;//定义指向struct node 结构体变量的指针变量
    int pw = 123;
    int paw = 0;
    printf("请输入登录密码：\n");
    scanf("%d", &paw);
    if (paw == pw)
    {
        printf("密码正确\n");
        while (1)
        {
            int n;
            menu();
            printf("请输入:>\n");
            scanf("%d", &n);
            switch (n)
            {
            case 0:
                printf("退出:>\n");
                return 0; 
                break;
            case 1:
                create(&head);//创建链表函数,增加信息
                break;
            case 2: 
                search(head);//查找信息 
                break;
            case 3: 
                revise(&head);//修改管理表
                break;
            case 4:
                delete(&head);//删除管理表
                break;
            case 5:
                print(head);//打印信息
                break;
            case 6:
                count(head);//计算每个设备金额
                break;
            case 7:
                stats(head);//统计设备总数量和总金额
                break;
            default:
                printf("输入错误，请重新输入\n");
                break;
            }
        }
    }
    else 
    {
        printf("密码错误，退出;>\n");
        exit(0);
    }
    return 0;
}
