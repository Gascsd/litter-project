#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include "data_struct_base.hpp"

struct Passenger // �˿���Ϣ�ṹ��
{
    std::string _name; // �ͻ�����
    std::string _ID; // ���֤��
    Passenger() : _name(""), _ID("") {}
    Passenger(std::string& name, std::string& id) // ���캯��
        : _name(name), _ID(id) {}
};

struct FlightInfo // ������Ϣ�ṹ��
{
    std::string _flightNo; // �����
    std::string _departureAirport; // ������
    std::string _arrivalAirport; // Ŀ�ĵ�
    std::string _departureTime; // ����ʱ��
    std::string _arrivalTime; // ����ʱ��
    int _price = 800; // Ʊ��
    int _fixedSeats = 120; // ����˿���
    int _remainedSeats = 120; // ʣ����λ��
    my::list<Passenger> _passengerList; // ��Ա����

    // ���캯��������ͨ����������ʼ��������Ϣ
    FlightInfo() : _flightNo(""), _departureAirport(""), _arrivalAirport(""), _departureTime(""), _arrivalTime(""), _price(800), _fixedSeats(120), _remainedSeats(120), _passengerList() {}
    FlightInfo(std::string& flightNo, std::string& departureAirport, std::string& arrivalAirport, std::string& departureTime, std::string& arrivalTime, int price, int fixedSeats)
        : _flightNo(flightNo), _departureAirport(departureAirport), _arrivalAirport(arrivalAirport), _departureTime(departureTime), _arrivalTime(arrivalTime), _price(price), _fixedSeats(fixedSeats)
    {
        _remainedSeats = _fixedSeats;
    }
};


enum//ö��ϵͳ�Ĳ���
{
    EXIT,//�˳�
    BOOK,//��Ʊ
    REFUND,//��Ʊ
    VIEW,//���������Ϣ
    CHECK,//��ѯ������Ϣ
};



//��������
void System();//ϵͳ�����������ǽ���ϵͳ�����
void menu();//�˵���������ӡ�����б�ѡ����
void BookTicket(my::vector<FlightInfo>& flight);//��Ʊ����
void RefundTicket(my::vector<FlightInfo>& flight);//��Ʊ����
void ViewFlightInfo(my::vector<FlightInfo>& flight);//��ʾ���к�����Ϣ
void CheckFlightInfo(my::vector<FlightInfo>& flight);//��ѯ������Ϣ
void saveFile(my::vector<FlightInfo>& flight);//д�ļ�
void readFile(my::vector<FlightInfo>& flight);//���ļ�
void add_flight(my::vector<FlightInfo>& flight);//���Ӻ���


