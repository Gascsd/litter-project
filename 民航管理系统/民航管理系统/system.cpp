#include "system.h"
using namespace std;
void menu()
{
	cout << "*******��ӭʹ�ú��չ���ϵͳ*******" << endl;
	cout << "*******[1]��Ʊ        ************" << endl;
	cout << "*******[2]��Ʊ        ************" << endl;
	cout << "*******[3]���������Ϣ************" << endl;
	cout << "*******[4]��ѯ������Ϣ************" << endl;
	cout << "*******[0]�˳�        ************" << endl;
	cout << "**********************************" << endl;
}
void add_flight(my::vector<FlightInfo>& flight)//���Ӻ�����Ϣ
{
    int i = 3;
    while (i--)
    {
        string flightNo, start, end, startTime, endTime;
        int price, fixed;
        cout << "��ֱ����뺽��ţ������أ�Ŀ�ĵأ�����ʱ�䣬����ʱ�䣬Ʊ�ۣ��˿Ͷ���" << endl;
        cin >> flightNo >> start >> end >> startTime >> endTime >> price >> fixed;
        FlightInfo tmp(flightNo, start, end, startTime, endTime, price, fixed);
        flight.push_back(tmp);
    }
}
void view(my::vector<FlightInfo>& flight)//��ӡ���к�����Ϣ
{
    printf("�����\t������\tĿ�ĵ�\t����ʱ��\t����ʱ��\tƱ��\t����˿���\tʣ����λ��\t\n");
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
    cout << "������ҪԤ���ĺ�����:";
    int input = 0;
    cin >> input;
    if (input >= 1 && input <= flight.size() && flight[input-1]._remainedSeats > 0)//�����±�Ϸ���������Ʊ���ܹ�Ʊ
    {
        string name;
        string didentify;
        //flight[input-1]
        cout << "������������";
        cin >> name;
        cout << "���������֤�ţ�";
        cin >> didentify;
        Passenger tmp(name, didentify);
        flight[input - 1]._passengerList.push_back(tmp);
        flight[input - 1]._remainedSeats--;
        cout << "��Ʊ�ɹ�" << endl;
    }
    else
    {
        cout << "��������" << endl;
    }
    system("pause");
}
void RefundTicket(my::vector<FlightInfo>& flight)
{
    cout << "RefundTicket" << endl;
    view(flight);
    cout << "������Ҫ��Ʊ�ĺ�����:";
    int input = 0;
    cin >> input;
    if (input >= 1 && input <= flight.size() && flight[input - 1]._remainedSeats < flight[input - 1]._fixedSeats)//�����±�Ϸ������Ѿ����˹�Ʊ�˲�����Ʊ
    {
        cout << "������Ҫ��Ʊ������" << endl;
        string name;
        cin >> name;
        auto begin = flight[input - 1]._passengerList.begin();
        while (begin != flight[input - 1]._passengerList.end())
        {
            if ((*begin)._name == name)//�ҵ�����Ҫ�����Ʊ��
            {
                flight[input - 1]._passengerList.erase(begin);
                flight[input - 1]._remainedSeats++;
                cout << "��Ʊ�ɹ�" << endl;
                system("pause");
                return;
            }
        }
        cout << "û�иó˿�" << endl;
        system("pause");
        return;
    }
    else
    {
        cout << "��������" << endl;
    }
    system("pause");
}

void ViewFlightInfo(my::vector<FlightInfo>& flight)
{
    cout << "������Ϣ����" << endl;
    view(flight);
    system("pause");
}
void check_menu()//��ѯ��ʽ�˵�
{
    cout << "*********��ѡ���ѯ��ʽ**********" << endl;
    cout << "*********[1]����Ų�ѯ***********" << endl;
    cout << "*********[2]����ʱ���ѯ**********" << endl;
    cout << "*******************************" << endl;
    cout << "�����룺>" << endl;
}
void FlightNoCheck(my::vector<FlightInfo>& flight)//����Ų�ѯ
{
    string flightNo;
    cin >> flightNo;
    for (auto f : flight)
    {
        if (f._flightNo == flightNo)
        {
            cout << "�����\t������\tĿ�ĵ�\t����ʱ��\t����ʱ��\tƱ��\t����˿���\tʣ����λ��\t\n";
            printf("%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t\n",
                f._flightNo.c_str(), f._departureAirport.c_str(), f._arrivalAirport.c_str(),
                f._departureTime.c_str(), f._arrivalTime.c_str(), f._price, f._fixedSeats, f._remainedSeats);
            cout << "�˿���Ϣ��" << endl;
            cout << "���֤��\t���֤��\n";
            for (auto e : f._passengerList)
            {
                printf("%s\t%s\n", e._name, e._ID);
            }
            return;
        }
    }
    cout << "û�иú�����Ϣ" << endl;
}
void departureTimeCheck(my::vector<FlightInfo>& flight)//����ʱ���ѯ
{
    string departureAirport;
    cin >> departureAirport;
    for (auto f : flight)
    {
        if (f._departureAirport == departureAirport)
        {
            cout << "�����\t������\tĿ�ĵ�\t����ʱ��\t����ʱ��\tƱ��\t����˿���\tʣ����λ��\t\n";
            printf("%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t\n",
                f._flightNo.c_str(), f._departureAirport.c_str(), f._arrivalAirport.c_str(),
                f._departureTime.c_str(), f._arrivalTime.c_str(), f._price, f._fixedSeats, f._remainedSeats);
            cout << "�˿���Ϣ��" << endl;
            cout << "����\t���֤��\n";
            for (auto e : f._passengerList)
            {
                printf("%s\t%s\n", e._name.c_str(), e._ID.c_str());
            }
            return;
        }
    }
    cout << "û�иú�����Ϣ" << endl;
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
        cout << "�����뺽���" << endl;
        FlightNoCheck(flight);
        break;
    case 2:
        cout << "�����뺽��ʱ��" << endl;
        departureTimeCheck(flight);
        break;
    default:
        cout << "��������" << endl;
    }
    system("pause");
}


FlightInfo parseFlightInfo(const char* str) // ���ַ�������Ϊ������Ϣ
{
    constexpr char DELIMITER[] = " ";
    FlightInfo fi;
    // ʹ��strtok�������տո�ָ��ַ���
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
    while (fgets(buffer, 1024, fp)) // ���ж�ȡ�ļ���ֱ����ȡ���ļ�ĩβ
    {
        // �����ȡ����FlightInfo����ʶ����˵�����µĺ�����Ϣ��Ҫ��ȡ
        if (string(buffer) == string("FlightInfo:\n"))
        {
            fi = FlightInfo();
            fgets(buffer, 1024, fp);
            //sscanf(buffer, "%s%s%s%s%s%d%d%d", fi._flightNo, fi._departureAirport, fi._arrivalAirport, fi._departureTime, fi._arrivalTime, &fi._price, &fi._fixedSeats, &fi._remainedSeats);
            fi = parseFlightInfo(buffer);
            //printf("%s", buffer);
        }
        //�������PassengerList����˵��Ҫ��ʼ��ȡ�˿���Ϣ��
        if (string(buffer) == string("PassengerList:\n"))
        {
            fgets(buffer, 1024, fp);
            fi._passengerList.clear(); //���ԭ������
            while (string(buffer) != string("EndOfFlightInfo\n"))//��û�ж�����β��־ʱ����ȡ�˿���Ϣ
            {
                pg = Passenger();
                sscanf(buffer, "%s %s", pg._name, pg._ID);
                fi._passengerList.push_back(pg);
            }
            flight.push_back(fi);
        }
    }
}
void saveFile(my::vector<FlightInfo>& flight)//д�ļ�
{
    FILE* fp = fopen("FlightInfo.txt", "w"); // ���ļ�
    if (!fp) // �ж��ļ��Ƿ�ɹ���
    {
        printf("Cannot open the file!\n");
        return;
    }
    // �������ؽ�flight�ڵ�����д���ļ�
    for (auto f : flight)
    {
        fprintf(fp, "FlightInfo:\n"); // д��ͷ����ʶ
        fprintf(fp, "%s ", f._flightNo.c_str()); // д�뺽����Ϣ
        fprintf(fp, "%s ", f._departureAirport.c_str());
        fprintf(fp, "%s ", f._arrivalAirport.c_str());
        fprintf(fp, "%s ", f._departureTime.c_str());
        fprintf(fp, "%s ", f._arrivalTime.c_str());
        fprintf(fp, "%d ", f._price);
        fprintf(fp, "%d ", f._fixedSeats);
        fprintf(fp, "%d\n", f._remainedSeats);
        fprintf(fp, "PassengerList:\n");
        for (auto p : f._passengerList) // д��˿���Ϣ
        {
            fprintf(fp, "%s %s\n", p._name.c_str(), p._ID.c_str());
        }
        fprintf(fp, "EndOfFlightInfo\n"); // д��ͷ����ʶ
    }
    fclose(fp); // �ر��ļ�
}






