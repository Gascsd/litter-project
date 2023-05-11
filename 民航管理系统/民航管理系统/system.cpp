#include "system.h"
using namespace std;
void menu()
{
	cout << "*******欢迎使用航空管理系统*******" << endl;
	cout << "*******[1]订票        ************" << endl;
	cout << "*******[2]退票        ************" << endl;
	cout << "*******[3]浏览航班信息************" << endl;
	cout << "*******[4]查询航班信息************" << endl;
	cout << "*******[0]退出        ************" << endl;
	cout << "**********************************" << endl;
}
void add_flight(my::vector<FlightInfo>& flight)//增加航班信息
{
    int i = 3;
    while (i--)
    {
        string flightNo, start, end, startTime, endTime;
        int price, fixed;
        cout << "请分别输入航班号，出发地，目的地，出发时间，到达时间，票价，乘客定额" << endl;
        cin >> flightNo >> start >> end >> startTime >> endTime >> price >> fixed;
        FlightInfo tmp(flightNo, start, end, startTime, endTime, price, fixed);
        flight.push_back(tmp);
    }
}
void view(my::vector<FlightInfo>& flight)//打印所有航班信息
{
    printf("航班号\t出发地\t目的地\t出发时间\t到达时间\t票价\t定额乘客数\t剩余座位数\t\n");
    int i = 0;
    for (auto& f : flight)
    {
        i++;
        printf("[%d]%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t\n",
            i, f._flightNo.c_str(), f._departureAirport.c_str(), f._arrivalAirport.c_str(),
            f._departureTime.c_str(), f._arrivalTime.c_str(), f._price, f._fixedSeats, f._remainedSeats);
    }
}
void BookTicket(my::vector<FlightInfo>& flight)
{
    view(flight);
    cout << "请输入要预定的航班编号:";
    int input = 0;
    cin >> input;
    if (input >= 1 && input <= flight.size() && flight[input-1]._remainedSeats > 0)//输入下标合法并且有余票才能购票
    {
        string name;
        string didentify;
        //flight[input-1]
        cout << "请输入姓名：";
        cin >> name;
        cout << "请输入身份证号：";
        cin >> didentify;
        Passenger tmp(name, didentify);
        flight[input - 1]._passengerList.push_back(tmp);
        flight[input - 1]._remainedSeats--;
        cout << "订票成功" << endl;
    }
    else
    {
        cout << "输入有误" << endl;
    }
    system("pause");
}
void RefundTicket(my::vector<FlightInfo>& flight)
{
    cout << "RefundTicket" << endl;
    view(flight);
    cout << "请输入要退票的航班编号:";
    int input = 0;
    cin >> input;
    if (input >= 1 && input <= flight.size() && flight[input - 1]._remainedSeats < flight[input - 1]._fixedSeats)//输入下标合法并且已经有人购票了才能退票
    {
        cout << "请输入要退票的姓名" << endl;
        string name;
        cin >> name;
        auto begin = flight[input - 1]._passengerList.begin();
        while (begin != flight[input - 1]._passengerList.end())
        {
            if ((*begin)._name == name)//找到符合要求的退票者
            {
                flight[input - 1]._passengerList.erase(begin);
                flight[input - 1]._remainedSeats++;
                cout << "退票成功" << endl;
                system("pause");
                return;
            }
        }
        cout << "没有该乘客" << endl;
        system("pause");
        return;
    }
    else
    {
        cout << "输入有误" << endl;
    }
    system("pause");
}

void ViewFlightInfo(my::vector<FlightInfo>& flight)
{
    cout << "航班信息如下" << endl;
    view(flight);
    system("pause");
}
void check_menu()//查询方式菜单
{
    cout << "*********请选择查询方式**********" << endl;
    cout << "*********[1]航班号查询***********" << endl;
    cout << "*********[2]航班时间查询**********" << endl;
    cout << "*******************************" << endl;
    cout << "请输入：>" << endl;
}
void FlightNoCheck(my::vector<FlightInfo>& flight)//航班号查询
{
    string flightNo;
    cin >> flightNo;
    for (auto f : flight)
    {
        if (f._flightNo == flightNo)
        {
            cout << "航班号\t出发地\t目的地\t出发时间\t到达时间\t票价\t定额乘客数\t剩余座位数\t\n";
            printf("%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t\n",
                f._flightNo.c_str(), f._departureAirport.c_str(), f._arrivalAirport.c_str(),
                f._departureTime.c_str(), f._arrivalTime.c_str(), f._price, f._fixedSeats, f._remainedSeats);
            cout << "乘客信息：" << endl;
            cout << "身份证号\t身份证号\n";
            for (auto e : f._passengerList)
            {
                printf("%s\t%s\n", e._name, e._ID);
            }
            return;
        }
    }
    cout << "没有该航班信息" << endl;
}
void departureTimeCheck(my::vector<FlightInfo>& flight)//航班时间查询
{
    string departureAirport;
    cin >> departureAirport;
    for (auto f : flight)
    {
        if (f._departureAirport == departureAirport)
        {
            cout << "航班号\t出发地\t目的地\t出发时间\t到达时间\t票价\t定额乘客数\t剩余座位数\t\n";
            printf("%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t\n",
                f._flightNo.c_str(), f._departureAirport.c_str(), f._arrivalAirport.c_str(),
                f._departureTime.c_str(), f._arrivalTime.c_str(), f._price, f._fixedSeats, f._remainedSeats);
            cout << "乘客信息：" << endl;
            cout << "姓名\t身份证号\n";
            for (auto e : f._passengerList)
            {
                printf("%s\t%s\n", e._name.c_str(), e._ID.c_str());
            }
            return;
        }
    }
    cout << "没有该航班信息" << endl;
}

void CheckFlightInfo(my::vector<FlightInfo>& flight)
{
    cout << "CheckFlightInfo" << endl;
    check_menu();
    int input = 0;
    cin >> input;
    switch (input)
    {
    case 1:
        cout << "请输入航班号" << endl;
        FlightNoCheck(flight);
        break;
    case 2:
        cout << "请输入航班时间" << endl;
        departureTimeCheck(flight);
        break;
    default:
        cout << "输入有误" << endl;
    }
    system("pause");
}


FlightInfo parseFlightInfo(const char* str) // 将字符串解析为航班信息
{
    constexpr char DELIMITER[] = " ";
    FlightInfo fi;
    // 使用strtok函数按照空格分割字符串
    char* token = std::strtok(const_cast<char*>(str), DELIMITER);
    fi._flightNo = token;
    token = std::strtok(nullptr, DELIMITER);
    fi._departureAirport = token;
    token = std::strtok(nullptr, DELIMITER);
    fi._arrivalAirport = token;
    token = std::strtok(nullptr, DELIMITER);
    fi._departureTime = token;
    token = std::strtok(nullptr, DELIMITER);
    fi._arrivalTime = token;
    token = std::strtok(nullptr, DELIMITER);
    fi._price = std::atoi(token);
    token = std::strtok(nullptr, DELIMITER);
    fi._fixedSeats = std::atoi(token);
    token = std::strtok(nullptr, DELIMITER);
    fi._remainedSeats = std::atoi(token);
    return fi;
}

void readFile(my::vector<FlightInfo>&flight)
{
    FILE* fp = fopen("FlightInfo.txt", "r");
    if (!fp)
    {
        printf("Cannot open the file!\n");
        return;
    }
    char buffer[1024];
    FlightInfo fi;
    Passenger pg;
    while (fgets(buffer, 1024, fp)) // 逐行读取文件，直到读取到文件末尾
    {
        // 如果读取到“FlightInfo”标识，则说明有新的航班信息需要读取
        if (string(buffer) == string("FlightInfo:\n"))
        {
            fi = FlightInfo();
            fgets(buffer, 1024, fp);
            //sscanf(buffer, "%s%s%s%s%s%d%d%d", fi._flightNo, fi._departureAirport, fi._arrivalAirport, fi._departureTime, fi._arrivalTime, &fi._price, &fi._fixedSeats, &fi._remainedSeats);
            fi = parseFlightInfo(buffer);
            //printf("%s", buffer);
        }
        //如果读到PassengerList，则说明要开始读取乘客信息了
        if (string(buffer) == string("PassengerList:\n"))
        {
            fgets(buffer, 1024, fp);
            fi._passengerList.clear(); //清空原有数据
            while (string(buffer) != string("EndOfFlightInfo\n"))//在没有读到结尾标志时，读取乘客信息
            {
                pg = Passenger();
                sscanf(buffer, "%s %s", pg._name, pg._ID);
                fi._passengerList.push_back(pg);
            }
            flight.push_back(fi);
        }
    }
}
void saveFile(my::vector<FlightInfo>& flight)//写文件
{
    FILE* fp = fopen("FlightInfo.txt", "w"); // 打开文件
    if (!fp) // 判断文件是否成功打开
    {
        printf("Cannot open the file!\n");
        return;
    }
    // 逐个航班地将flight内的内容写入文件
    for (auto f : flight)
    {
        fprintf(fp, "FlightInfo:\n"); // 写入头部标识
        fprintf(fp, "%s ", f._flightNo.c_str()); // 写入航班信息
        fprintf(fp, "%s ", f._departureAirport.c_str());
        fprintf(fp, "%s ", f._arrivalAirport.c_str());
        fprintf(fp, "%s ", f._departureTime.c_str());
        fprintf(fp, "%s ", f._arrivalTime.c_str());
        fprintf(fp, "%d ", f._price);
        fprintf(fp, "%d ", f._fixedSeats);
        fprintf(fp, "%d\n", f._remainedSeats);
        fprintf(fp, "PassengerList:\n");
        for (auto p : f._passengerList) // 写入乘客信息
        {
            fprintf(fp, "%s %s\n", p._name.c_str(), p._ID.c_str());
        }
        fprintf(fp, "EndOfFlightInfo\n"); // 写入头部标识
    }
    fclose(fp); // 关闭文件
}






