#include "system.h"
using namespace std;


void Test()//测试文件操作
{
    my::vector<FlightInfo> flight;
    readFile(flight);
    add_flight(flight);
    saveFile(flight);
}

void System()
{
    system("cls");
    cout << "欢迎使用航空管理系统" << endl;
    my::vector<FlightInfo> flight;
    readFile(flight);
    int input = 0;
    do
    {
        menu();
        cout << "请输入序号:>";
        cin >> input;
        switch (input)
        {
        case EXIT:
            printf("退出系统...\n");
            saveFile(flight);
            break;
        case BOOK:
            //订票函数
            BookTicket(flight);
            system("cls");
            break;
        case REFUND:
            //退票函数
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
            printf("输入错误，请重新输入\n");
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
        cout << "请选择是否进入系统：\n0.退出\n1.进入系统\n";
        cin >> input;
        switch (input)
        {
        case 1:
            cout << "进入系统......" << endl;
            system("pause");
            System();
            break;
        case 0:
            cout << "退出系统......" << endl;
            break;
        default:
            cout << "输入非法，请重新输入" << endl;
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
