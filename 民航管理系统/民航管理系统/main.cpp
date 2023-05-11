#include "system.h"
using namespace std;


void Test()//�����ļ�����
{
    my::vector<FlightInfo> flight;
    readFile(flight);
    add_flight(flight);
    saveFile(flight);
}

void System()
{
    system("cls");
    cout << "��ӭʹ�ú��չ���ϵͳ" << endl;
    my::vector<FlightInfo> flight;
    readFile(flight);
    int input = 0;
    do
    {
        menu();
        cout << "���������:>";
        cin >> input;
        switch (input)
        {
        case EXIT:
            printf("�˳�ϵͳ...\n");
            saveFile(flight);
            break;
        case BOOK:
            //��Ʊ����
            BookTicket(flight);
            system("cls");
            break;
        case REFUND:
            //��Ʊ����
            RefundTicket(flight);
            system("cls");
            break;
        case VIEW:
            ViewFlightInfo(flight);
            system("cls");
            break;
        case CHECK:
            CheckFlightInfo(flight);
            system("cls");
            break;
        default:
            printf("�����������������\n");
            system("cls");
            system("pause");
        }
    } while (input);
}

int _main()
{
    int input = 0;
    do
    {
        system("cls");
        cout << "��ѡ���Ƿ����ϵͳ��\n0.�˳�\n1.����ϵͳ\n";
        cin >> input;
        switch (input)
        {
        case 1:
            cout << "����ϵͳ......" << endl;
            system("pause");
            System();
            break;
        case 0:
            cout << "�˳�ϵͳ......" << endl;
            break;
        default:
            cout << "����Ƿ�������������" << endl;
            system("pause");
        }
    } while (input);
    return 0;
}

int main()
{
    //Test();
    _main();
    return 0;
}
