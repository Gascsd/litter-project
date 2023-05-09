//
//  System.h
//  民航管理系统
//
//  Created by zht on 2023/5/9.
//

#ifndef System_h
#define System_h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//枚举操作内容
enum
{
    EXIT,//退出
    BOOK,//订票
    REFUND,//退票
    VIEW,//浏览航班信息
    CHECK,//查询航班信息
};

//结构体定义
//订票客户结构体定义
typedef struct Book
{
    char flightNum[8];//航班号
    char name[20];//客户姓名
    char didentify[6];//身份证号
    int grade;
    struct Book* next;//指向下一个乘客
}Book;

//航班信息结构体定义,每个航班号都会有不同的乘客名单，所以每个航班都应该有一个链表
typedef struct FlightInfo
{
    char flightNo[8];//航班号
    char start[6];//出发地
    char end[6];//目的地
    char sche[6];//飞行日
    char startTime[8];//出发时间
    char endTime[8];//到达时间
    int  price;//票价
    int  fixed;//乘客定额
    int  remained;//余票
    Book* order;//指向乘员名单链表的头指针，通过这个指针就可以找到所有乘客的名单了
    struct FlightInfo* next;//指向下一个航班
}FlightInfo;

typedef struct
{
    FlightInfo head;
    size_t size;
}Flight;


//函数声明
void System();//系统函数，这里是进入系统的入口
void menu();//菜单函数，打印功能列表，选择功能
void BookTicket();//订票函数
void RefundTicket();//退票函数
void ViewFlightInfo();//显示所有航班信息
void CheckFlightInfo();//查询制定航班信息
void read_file(Flight* pfight);//读文件











#endif /* System_h */
