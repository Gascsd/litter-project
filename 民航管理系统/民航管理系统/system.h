#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include "data_struct_base.hpp"

struct Passenger // 乘客信息结构体
{
    std::string _name; // 客户姓名
    std::string _ID; // 身份证号
    Passenger() : _name(""), _ID("") {}
    Passenger(std::string& name, std::string& id) // 构造函数
        : _name(name), _ID(id) {}
};

struct FlightInfo // 航班信息结构体
{
    std::string _flightNo; // 航班号
    std::string _departureAirport; // 出发地
    std::string _arrivalAirport; // 目的地
    std::string _departureTime; // 出发时间
    std::string _arrivalTime; // 到达时间
    int _price = 800; // 票价
    int _fixedSeats = 120; // 定额乘客数
    int _remainedSeats = 120; // 剩余座位数
    my::list<Passenger> _passengerList; // 乘员名单

    // 构造函数，可以通过参数来初始化航班信息
    FlightInfo() : _flightNo(""), _departureAirport(""), _arrivalAirport(""), _departureTime(""), _arrivalTime(""), _price(800), _fixedSeats(120), _remainedSeats(120), _passengerList() {}
    FlightInfo(std::string& flightNo, std::string& departureAirport, std::string& arrivalAirport, std::string& departureTime, std::string& arrivalTime, int price, int fixedSeats)
        : _flightNo(flightNo), _departureAirport(departureAirport), _arrivalAirport(arrivalAirport), _departureTime(departureTime), _arrivalTime(arrivalTime), _price(price), _fixedSeats(fixedSeats)
    {
        _remainedSeats = _fixedSeats;
    }
};


enum//枚举系统的操作
{
    EXIT,//退出
    BOOK,//订票
    REFUND,//退票
    VIEW,//浏览航班信息
    CHECK,//查询航班信息
};



//函数声明
void System();//系统函数，这里是进入系统的入口
void menu();//菜单函数，打印功能列表，选择功能
void BookTicket(my::vector<FlightInfo>& flight);//订票函数
void RefundTicket(my::vector<FlightInfo>& flight);//退票函数
void ViewFlightInfo(my::vector<FlightInfo>& flight);//显示所有航班信息
void CheckFlightInfo(my::vector<FlightInfo>& flight);//查询航班信息
void saveFile(my::vector<FlightInfo>& flight);//写文件
void readFile(my::vector<FlightInfo>& flight);//读文件
void add_flight(my::vector<FlightInfo>& flight);//增加航班


