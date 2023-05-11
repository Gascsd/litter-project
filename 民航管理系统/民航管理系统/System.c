#include "System.h"

void menu()
{
    printf("******************************\n");
    printf("*********�񺽹���ϵͳ*********\n");
    printf("*********1.��Ʊ***************\n");
    printf("*********2.��Ʊ***************\n");
    printf("*********3.���������Ϣ*******\n");
    printf("*********4.��ѯ������Ϣ*******\n");
    printf("*********0.�˳�ϵͳ***********\n");
    printf("******************************\n");
}
void BookTicket()
{
    printf("��Ʊ\n");
    //    ViewFlightInfo();
    //    printf("��ѡ��Ҫ���ĺ�����ţ�");
    //    int no = 0;
    //    scanf("%d", &no);

}
void RefundTicket()
{
    printf("��Ʊ\n");
}
void ViewFlightInfo(Flight* pfight)
{
    printf("��ʾ������Ϣ\n");
    //��ӡ��ͷ ����� ������ Ŀ�ĵ� ����ʱ�� ����ʱ�� Ʊ�� �˿Ͷ��� ��Ʊ
    printf("�����\t������\tĿ�ĵ�\t����ʱ��\t����ʱ��\tƱ��\t�˿Ͷ���\t��Ʊ\n");
    FlightInfo* cur = pfight->head.next;
    for (size_t i = 0; i < pfight->size; ++i)
    {
        printf("%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\n", cur->flightNo, cur->start, cur->end, cur->startTime, cur->endTime, cur->price, cur->fixed, cur->remained);
        cur = cur->next;
    }
}
void CheckFlightInfo()
{
    printf("��ѯ������Ϣ\n");
}
void read_file(Flight* pflight)
{
    //��������Ϣ�ļ�
    FILE* fp = fopen("FlightInfoFlie.txt", "r");
    if (!fp)//��ȡʧ��
    {
        return;
    }
    while (1)
    {
        FlightInfo* newnode = (FlightInfo*)malloc(sizeof(FlightInfo));
        if (!newnode)
        {
            printf("��ȡ�ļ�ʧ�ܣ��˳�����...\n");
            exit(-1);
        }
        else
        {
            if (fread(newnode, sizeof(FlightInfo), 1, fp) < 1)
                break;//��ȡ����
            //ͷ�庽��� 
            newnode->next = pflight->head.next;
            pflight->head.next = newnode;
            pflight->size++;
        }
    }
    fclose(fp);
    //���˿���Ϣ
    fp = fopen("Book.txt", "r");
    if (!fp)//��ȡʧ��
    {
        return;
    }
    while (1)
    {
        Book* newnode = (Book*)malloc(sizeof(Book));
        if (!newnode)
        {
            printf("��ȡ�ļ�ʧ�ܣ��˳�����...\n");
            exit(-1);
        }
        else
        {
            if (fread(newnode, sizeof(Book), 1, fp) < 1)
                break;//��ȡ����
            //ͷ��˿�
            //�������������ҵ�newnode�ĺ���ţ�Ȼ��ͷ��
            FlightInfo* cur = pflight->head.next;
            while (cur)
            {
                if (strcmp(newnode->flightNum, cur->flightNo) == 0)
                {
                    //�ҵ���Ӧ�ĺ�����ˣ�ͷ��newnode
                    newnode->next = cur->order;
                    cur->order = newnode;
                }
                cur = cur->next;
            }
        }
    }
    fclose(fp);
}
void add_flight(Flight* pfight)
{
    char flightNo[8];//�����
    char start[6];//������
    char end[6];//Ŀ�ĵ�
    char startTime[8];//����ʱ��
    char endTime[8];//����ʱ��
    int  price;//Ʊ��
    int  fixed;//�˿Ͷ���
    int  remained;//��Ʊ
    Book* order;//ָ���Ա���������ͷָ�룬ͨ�����ָ��Ϳ����ҵ����г˿͵�������
    struct FlightInfo* next;//ָ����һ������
}
void save_file(Flight* pfight)
{
    //д�뺽����Ϣ�ļ�
    FILE* fp = fopen("FlightInfoFlie.txt", "w+");
    if (!fp)
        return;
    FlightInfo* cur = pfight->head.next;
    while (cur)
    {
        fwrite(cur, sizeof(FlightInfo), 1, fp);
        cur = cur->next;
    }
    //д��˿���Ϣ
    fp = fopen("Book.txt", "w+");
    if (!fp)
        return;
    //���������б��õ��˿�����Ȼ��д��
    cur = pfight->head.next;
    while (cur)
    {
        Book* tmp = cur->order;
        while (tmp)
        {
            fwrite(tmp, sizeof(Book), 1, fp);
            tmp = tmp->next;
        }
        cur = cur->next;
    }
}
void System()
{
    printf("��ӭʹ���񺽹���ϵͳ\n");
    //���ȶ�ȡ�ļ���Ϣ
    Flight flight;
    read_file(&flight);
    //ϵͳ��ʼ����
    int input = 0;
    do
    {
        menu();
        printf("�����룺>");
        scanf("%d", &input);
        switch (input)
        {
        case EXIT:
            printf("�˳�ϵͳ...\n");
            break;
        case BOOK:
            //��Ʊ����
            BookTicket();
            break;
        case REFUND:
            //��Ʊ����
            RefundTicket();
            break;
        case VIEW:
            ViewFlightInfo(&flight);
            break;
        case CHECK:
            CheckFlightInfo();
            break;
        default:
            printf("�����������������\n");
        }
    } while (input);
}
