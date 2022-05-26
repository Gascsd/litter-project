#define _CRT_SECURE_NO_WARNINGS 1

#include"system.h"

void menu()
{
    printf("*****************************************************\n");
    printf("***************   计算机设备管理            *********\n");
    printf("*****************************************************\n");
    printf("***************   [1]建立管理表             *********\n");
    printf("***************   [2]查找指定设备编号的记录 *********\n");
    printf("***************   [3]修改管理表             *********\n");
    printf("***************   [4]删除管理表             *********\n");
    printf("***************   [5]输出管理表             *********\n");
    printf("***************   [6]计算每个设备金额       *********\n");
    printf("***************   [7]统计设备总数量和总金额 *********\n");
    printf("***************   [0]退出系统               *********\n");
    printf("*****************************************************\n");
}



void create(struct node** phead)//创建链表函数,增加信息
{
    int n;
    int i;
    printf("* * * * * * * * * * 建立管理表 * * * * * * * * * * *\n");
    printf("*****************************************************\n");
    printf("请输入记录的个数:");
    scanf("%d", &n);
    printf("\n");
    for (i = 0; i < n; i++)
    {
        struct node* newnode = (struct node*)malloc(sizeof(struct node));//开辟动态存储区
        printf("请输入设备编号：");
        scanf("%s", &newnode->no);//输入结构体变量struct node 中的成员no的值
        printf("\n");
        printf("请输入名称：");
        scanf("%s", &newnode->name);
        printf("\n");
        printf("请输入单价：");
        scanf("%lf", &newnode->dj);
        printf("\n");
        printf("请输入数量：");
        scanf("%d", &newnode->num);
        printf("\n");
        newnode->jine = newnode->dj * newnode->num;
        newnode->next = NULL;//赋给next空指针
        if (*phead == NULL)
            *phead = newnode;
        else
        {
            struct node* tail = *phead;//定义尾结点指针
            while (tail->next != NULL)
            {
                tail = tail->next;
            }
            tail->next = newnode;
        }
    }
    printf("\n输入完成!\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*****************************************************\n");
    system("pause");
}


void search(struct node* head)//查找信息 
{
    char n[12];
    struct node* temp = head;
    printf("请输入设备编号:");
    printf("\n");
    scanf("%s", n);
    while(temp != NULL)
    {
        if (strcmp(temp->no, n) == 0)
        {
            printf("\n查找完成!\n");
            printf("编号\t名称\t单价\t数量\t金额\t\n");
            printf("%s\t%s\t%.2f\t%d\t%.2f\n", temp->no, temp->name, temp->dj, temp->num, temp->jine);
            printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
            printf("*****************************************************\n");
            break;
        }
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("\n您输入的设备编号有误，无法查询！\n");
        printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
        printf("*****************************************************\n");
    }
    system("pause");

}

void revise(struct node** phead)//修改管理表
{
    char n[12];
    struct node* temp = *phead;
    printf("请输入要修改的设备编号:");
    printf("\n");
    scanf("%s", n);
    while (temp != NULL)
    {
        if (strcmp(temp->no, n) == 0)
        {
            printf("请输入设备编号：");
            scanf("%s", &temp->no);//输入结构体变量struct node 中的成员no的值
            printf("\n");
            printf("请输入名称：");
            scanf("%s", &temp->name);
            printf("\n");
            printf("请输入单价：");
            scanf("%lf", &temp->dj);
            printf("\n");
            printf("请输入数量：");
            scanf("%d", &temp->num);
            printf("\n");
            temp->jine = temp->dj * temp->num;
            printf("修改完成\n");
            printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
            printf("*****************************************************\n");
            break;
        }
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("\n您输入的设备编号有误，无法修改！\n");
        printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
        printf("*****************************************************\n");
    }
    system("pause");

}


void delete(struct node** phead)//删除管理表
{
    char n[12];
    struct node* temp = *phead;
    printf("请输入要删除的设备编号:");
    printf("\n");
    scanf("%s", n);
    if (temp == NULL)
    {
        printf("\n您输入的设备编号有误，无法删除！\n");
        printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
        printf("*****************************************************\n");
    }
    if (strcmp(temp->no, n) == 0)
    {
        *phead = temp->next;
        free(temp->next);
        temp->next = NULL;
        printf("删除完成\n");
    }
    while (temp->next != NULL)
    {
        if (strcmp(temp->next->no, n) == 0)
        {
            temp->next = temp->next->next;
            free(temp->next);
            temp->next = NULL;
            printf("删除完成\n");
            break;
        }
        temp = temp->next;
    }
    system("pause");
}



void print(struct node* head)//打印信息
{
    struct node* temp;
    temp = head;
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*****************************************************\n");
    printf("-------------------计算机设备管理表-------------------\n");
    printf("编号\t名称\t单价\t数量\t金额\t\n");
    while(temp != NULL)
    {
        printf("%s\t%s\t%.2f\t%d\t%.2f", temp->no, temp->name, temp->dj, temp->num, temp->jine);
        printf("\n");
        temp = temp->next;
    }
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*****************************************************\n");
    system("pause");
}


void count(struct node* head)//计算每个设备金额
{
    struct node* temp;
    temp = head;
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*****************************************************\n");
    printf("-------------------计算机设备管理表-------------------\n");
    printf("编号\t金额\t\n");
    while (temp != NULL)
    {
        printf("%s\t%.2f", temp->no, temp->jine);
        printf("\n");
        temp = temp->next;
    }
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*****************************************************\n");
    system("pause");
}



void stats(struct node* head)//统计总数量和总金额
{
    struct node* temp = head;
    double sum = 0;
    int count = 0;
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*****************************************************\n");
    printf("-------------------计算机设备管理表-------------------\n");
    while (temp != NULL)
    {
        sum += temp->jine;
        count += temp->num;
        temp = temp->next;
    }
    printf("总金额为：%.2lf\n", sum);
    printf("总数量为：%d\n", count);    
    system("pause");
}

int main()
{
    struct node* head = NULL;//定义指向struct node 结构体变量的指针变量
    int pw = 123;
    int paw = 0;
    while (1)
    {
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
                    //break;
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
            printf("密码错误，请选择下列操作>\n");
            printf("请输入0退出，或输入其他任意数字重新输入\n");
            int input = 0;
            scanf("%d", &input);
            if (input == 0)
                return 0;
        }
    }
    return 0;
}
