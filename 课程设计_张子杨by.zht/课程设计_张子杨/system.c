#define _CRT_SECURE_NO_WARNINGS 1

#include"system.h"

void menu()
{
    printf("*****************************************************\n");
    printf("***************   ������豸����            *********\n");
    printf("*****************************************************\n");
    printf("***************   [1]���������             *********\n");
    printf("***************   [2]����ָ���豸��ŵļ�¼ *********\n");
    printf("***************   [3]�޸Ĺ����             *********\n");
    printf("***************   [4]ɾ�������             *********\n");
    printf("***************   [5]��������             *********\n");
    printf("***************   [6]����ÿ���豸���       *********\n");
    printf("***************   [7]ͳ���豸���������ܽ�� *********\n");
    printf("***************   [0]�˳�ϵͳ               *********\n");
    printf("*****************************************************\n");
}



void create(struct node** phead)//����������,������Ϣ
{
    int n;
    int i;
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*****************************************************\n");
    printf("�������¼�ĸ���:");
    scanf("%d", &n);
    printf("\n");
    for (i = 0; i < n; i++)
    {
        struct node* newnode = (struct node*)malloc(sizeof(struct node));//���ٶ�̬�洢��
        printf("�������豸��ţ�");
        scanf("%s", &newnode->no);//����ṹ�����struct node �еĳ�Աno��ֵ
        printf("\n");
        printf("���������ƣ�");
        scanf("%s", &newnode->name);
        printf("\n");
        printf("�����뵥�ۣ�");
        scanf("%lf", &newnode->dj);
        printf("\n");
        printf("������������");
        scanf("%d", &newnode->num);
        printf("\n");
        newnode->jine = newnode->dj * newnode->num;
        newnode->next = NULL;//����next��ָ��
        if (*phead == NULL)
            *phead = newnode;
        else
        {
            struct node* tail = *phead;//����β���ָ��
            while (tail->next != NULL)
            {
                tail = tail->next;
            }
            tail->next = newnode;
        }
    }
    printf("\n�������!\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*****************************************************\n");
}


void search(struct node* head)//������Ϣ 
{
    char n[12];
    struct node* temp = head;
    printf("�������豸���:");
    printf("\n");
    scanf("%s", n);
    while(temp != NULL)
    {
        if (strcmp(temp->no, n) == 0)
        {
            printf("\n�������!\n");
            printf("���\t����\t����\t����\t���\t\n");
            printf("%s\t%s\t%.2f\t%d\t%.2f\n", temp->no, temp->name, temp->dj, temp->num, temp->jine);
            printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
            printf("*****************************************************\n");
            break;
        }
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("\n��������豸��������޷���ѯ��\n");
        printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
        printf("*****************************************************\n");
    }
}

void revise(struct node** phead)//�޸Ĺ����
{
    char n[12];
    struct node* temp = *phead;
    printf("������Ҫ�޸ĵ��豸���:");
    printf("\n");
    scanf("%s", n);
    while (temp != NULL)
    {
        if (strcmp(temp->no, n) == 0)
        {
            printf("�������豸��ţ�");
            scanf("%s", &temp->no);//����ṹ�����struct node �еĳ�Աno��ֵ
            printf("\n");
            printf("���������ƣ�");
            scanf("%s", &temp->name);
            printf("\n");
            printf("�����뵥�ۣ�");
            scanf("%lf", &temp->dj);
            printf("\n");
            printf("������������");
            scanf("%d", &temp->num);
            printf("\n");
            temp->jine = temp->dj * temp->num;
            printf("�޸����\n");
            printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
            printf("*****************************************************\n");
            break;
        }
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("\n��������豸��������޷��޸ģ�\n");
        printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
        printf("*****************************************************\n");
    }
}


void delete(struct node** phead)//ɾ�������
{
    char n[12];
    struct node* temp = *phead;
    printf("������Ҫɾ�����豸���:");
    printf("\n");
    scanf("%s", n);
    if (temp == NULL)
    {
        printf("\n��������豸��������޷�ɾ����\n");
        printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
        printf("*****************************************************\n");
    }
    if (strcmp(temp->no, n) == 0)
    {
        *phead = temp->next;
        free(temp->next);
        temp->next = NULL;
        printf("ɾ�����\n");
    }
    while (temp->next != NULL)
    {
        if (strcmp(temp->next->no, n) == 0)
        {
            temp->next = temp->next->next;
            free(temp->next);
            temp->next = NULL;
            printf("ɾ�����\n");
            break;
        }
        temp = temp->next;
    }
}



void print(struct node* head)//��ӡ��Ϣ
{
    struct node* temp;
    temp = head;
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*****************************************************\n");
    printf("-------------------������豸�����-------------------\n");
    printf("���\t����\t����\t����\t���\t\n");
    while(temp != NULL)
    {
        printf("%s\t%s\t%.2f\t%d\t%.2f", temp->no, temp->name, temp->dj, temp->num, temp->jine);
        printf("\n");
        temp = temp->next;
    }
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*****************************************************\n");
}


void count(struct node* head)//����ÿ���豸���
{
    struct node* temp;
    temp = head;
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*****************************************************\n");
    printf("-------------------������豸�����-------------------\n");
    printf("���\t���\t\n");
    while (temp != NULL)
    {
        printf("%s\t%.2f", temp->no, temp->jine);
        printf("\n");
        temp = temp->next;
    }
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*****************************************************\n");
}



void stats(struct node* head)//ͳ�����������ܽ��
{
    struct node* temp = head;
    double sum = 0;
    int count = 0;
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*****************************************************\n");
    printf("-------------------������豸�����-------------------\n");
    while (temp != NULL)
    {
        sum += temp->jine;
        count += temp->num;
        temp = temp->next;
    }
    printf("�ܽ��Ϊ��%lf\n", sum);
    printf("������Ϊ��%d\n", count);
}

