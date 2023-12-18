#pragma once
#include "head.h"

enum Status
{
	READER, // 0读者
	ADMIN   // 1图书管理员
};

struct Person //人
{
	Person() = default;
	Person(const string& stuno, const string& name, const string& passwd, const Status& status = READER, int borrowed = 0) //构造函数
		: _stuno(stuno)
		, _name(name)
		, _passwd(passwd)
		, _status(status)
		, _borrowed(borrowed)
	{

	}

	string _stuno;     //学号
	string _name;      //姓名
	Status _status;    //身份
	string _passwd;    //密码
	int _borrowed;     //借书的数量
};

class Admin : Person //管理员类 
{
public:
	//Admin() = default;//强制默认生成构造函数
	Admin() {}//默认构造
	
	void loadMessage() // 从文件中读取用户信息
	{
		ifstream fin;
		fin.open("用户信息.txt", ios::in);
		if (!fin.is_open())
		{
			cout << "载入数据失败，程序退出" << endl;
			exit(-1);
		}
		char buffer[1024] = { 0 };
		while (fin.getline(buffer, sizeof(buffer)))
		{
			//读取buffer中的数据构造Person对象
			vector<string> tmpV;
			char* token = strtok(buffer, " ");
			while (token != nullptr)
			{
				tmpV.push_back(token);
				token = strtok(nullptr, " ");
			}
			Status status = READER;
			if (tmpV[3] == "1") status = ADMIN;
			int num = stoi(tmpV[4]);
			Person p(tmpV[0], tmpV[1], tmpV[2], status, num);

			if (status == READER)
			{
				readerList.push_back(p);
			}
			else
			{
				adminList.push_back(p);
			}
		}
	}

	void saveMessage() // 保存信息到文件中
	{
		ofstream fout;
		fout.open("用户信息.txt", ios::out);
		if (!fout.is_open())
		{
			cout << "文件保存失败，无法退出" << endl;
		}
		//保存读者信息
		auto it1 = readerList.begin();
		while (it1 != readerList.end())
		{
			string buffer;
			//格式化书籍信息并保存在buffer中
			buffer += (it1->_stuno + " " + it1->_name + " " + it1->_passwd + " " + to_string(it1->_status) + " " + to_string(it1->_borrowed));

			fout << buffer << endl;//写入文件
			++it1;
		}
		auto it2 = adminList.begin();
		while (it2 != adminList.end())
		{
			string buffer;
			//格式化书籍信息并保存在buffer中
			buffer += (it2->_stuno + " " + it2->_name + " " + it2->_passwd + " " + to_string(it2->_status) + " " + to_string(it2->_borrowed));

			fout << buffer << endl;//写入文件
			++it2;
		}
		//cout << "保存成功" << endl;
	}
	//查找核对
	int find(const string& name, const string passwd) // 0 不存在该用户  1 密码错误 2 管理员 3 读者
	{
		auto it = readerList.begin();
		while (it != readerList.end())
		{
			if (it->_name == name)
			{
				if (it->_passwd == passwd)
					return 3;
				else
					return 1;
			}
			++it;
		}
		it = adminList.begin();
		while (it != adminList.end())
		{
			if (it->_name == name)
			{
				if (it->_passwd == passwd)
					return 2;
				else
					return 1;
			}
			++it;
		}
		return 0;
	}
	void addAdmin()//增加管理员
	{
		string name;
		string passwd;
		string stuno;
		cout << "请输入学号:";
		cin >> stuno;
		cout << "请输入用户名:";
		cin >> name;
		cout << "请输入密码:";
		cin >> passwd;
		Person p(stuno, name, passwd, ADMIN);
		adminList.push_back(p);
		cout << "添加管理员成功" << endl;
	}
	void addReader()//增加读者
	{
		string name;
		string passwd;
		string stuno;
		cout << "请输入学号:";
		cin >> stuno;
		cout << "请输入用户名:";
		cin >> name;
		cout << "请输入密码:";
		cin >> passwd;
		Person p(stuno, name, passwd, READER);
		readerList.push_back(p);
		cout << "添加读者成功" << endl;
	}
	void findAdmin()//查询管理员信息
	{
		int input = 0;
		cout << "查询所有管理员信息请输入1, 查询单个管理员信息请输入2:" << endl;
		cin >> input;
		if (input == 1)
		{
			printf("|管理员姓名  |管理员学号|密码\n");
			auto it = adminList.begin();
			while (it != adminList.end())
			{
				printf("|%-12s|%10s|%s\n", it->_name.c_str(), it->_stuno.c_str(), it->_passwd.c_str());
				++it;
			}
		}
		else if (input == 2)
		{
			string name;
			cout << "请输入要查询的管理员姓名:";
			cin >> name;
			auto it = adminList.begin();
			while (it != adminList.end())
			{
				if (it->_name == name)
				{
					printf("|管理员姓名  |管理员学号|密码\n");
					printf("|%-12s|%10s|%s\n", it->_name.c_str(), it->_stuno.c_str(), it->_passwd.c_str());
					return;
				}
				++it;
			}
			cout << "该用户不存在" << endl;
		}
		else
		{
			cout << "输入错误" << endl;
		}
	}
	void findReader()//查询读者信息
	{
		int input = 0;
		cout << "查询所有读者信息请输入1, 查询单个读者信息请输入2:" << endl;
		cin >> input;
		if (input == 1)
		{
			printf("|读者姓名    |读者学号  |借书数量|密码\n");
			auto it = readerList.begin();
			while (it != readerList.end())
			{
				printf("|%-12s|%10s|%8d|%s\n", it->_name.c_str(), it->_stuno.c_str(), it->_borrowed, it->_passwd.c_str());
				++it;
			}
		}
		else if (input == 2)
		{
			string name;
			cout << "请输入要查询的读者姓名:";
			cin >> name;
			auto it = readerList.begin();
			while (it != readerList.end())
			{
				if (it->_name == name)
				{
					printf("|读者姓名    |读者学号  |借书数量|密码\n");
					printf("|%-12s|%10s|%8d|%s\n", it->_name.c_str(), it->_stuno.c_str(), it->_borrowed, it->_passwd.c_str());
					return;
				}
				++it;
			}
			cout << "该用户不存在" << endl;
		}
		else
		{
			cout << "输入错误" << endl;
		}
	}
private:
	list<Person> adminList;
	list<Person> readerList;

};