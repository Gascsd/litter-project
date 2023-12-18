#pragma once
#include "head.h"
#include "Date.hpp"

struct Book
{
	Book(const string& name = "", int total = 0, int borrowed = 0)
		: _name(name)
		, _borrowed(borrowed)
		, _total(total) 
	{}
	void Print()
	{
		cout << "  书名:" << _name << endl;
		cout << "  共藏书:" << _total << "本" << endl;
		cout << "  已借出:" << _borrowed << "本" << endl;
		cout << "  剩余:" << _total - _borrowed << "本" << endl;
	}
	string _name;  // 书名
	int _borrowed; // 借出书的数量
	int _total;    // 藏书的总数量
};
struct BorrowInfo
{
	BorrowInfo(const string& bookName, const string& personName, Date date1 = Date(), Date date2 = Date())
		: _bookName(bookName)
		, _personName(personName)
	{
		if (date1 == Date())
		{
			time_t now = time(0);
			struct tm* nowtime = localtime(&now);
			Date d1(nowtime->tm_year + 1900, nowtime->tm_mon, nowtime->tm_mday);
			_borrowDate = d1;
			_returnDate = d1 + BORROWTIME;
		}
		else
		{
			_borrowDate = date1;
			_returnDate = date2;
		}
	}
	string _bookName;   // 书名
	string _personName; // 借书人姓名
	Date _borrowDate;   // 借书日期
	Date _returnDate;   // 最迟还书日期
};

class BookList
{
public:
	//从文件中加载相关信息
	void loadMessage()
	{
		ifstream fin;
		char buffer[1024] = { 0 };
		//加载书列表
		fin.open("书籍信息.txt", ios::in);
		if (!fin.is_open())
		{
			cout << "载入书籍信息失败，程序退出" << endl;
			exit(-1);
		}
		while (fin.getline(buffer, sizeof(buffer)))
		{
			//字符串格式然后构造book对象
			vector<string> tmpV;
			char* token = strtok(buffer, " ");
			while (token != nullptr)
			{
				tmpV.push_back(token);
				token = strtok(nullptr, " ");
			}
			if (tmpV.size() >= 3)
			{
				Book tmp(tmpV[0], stoi(tmpV[1]), stoi(tmpV[2]));
				bookList.insert(make_pair(tmpV[0], tmp)); //将book对象插入到bookList中
			}
		}
		fin.close();
		//加载借书表
		fin.open("借书信息.txt", ios::in);
		if (!fin.is_open())
		{
			cout << "载入借书信息失败，程序退出" << endl;
			exit(-1);
		}
		while (fin.getline(buffer, sizeof(buffer)))
		{
			//字符串格式然后构造borrowinfo对象
			vector<string> tmpV;
			char* token = strtok(buffer, " ");
			while (token != nullptr)
			{
				tmpV.push_back(token);
				token = strtok(nullptr, " ");
			}
			if (tmpV.size() >= 3)
			{
				BorrowInfo tmp(tmpV[0], tmpV[1], Date().stringtToDate(tmpV[2]), Date().stringtToDate(tmpV[3]));
				borrowList.push_back(tmp);
			}
		}
		fin.close();
	}
	//保存信息到文件中
	void saveMessage()
	{
		ofstream fout;
		//保存书籍信息
		fout.open("书籍信息.txt", ios::out);
		if (!fout.is_open())
		{
			cout << "文件保存失败，无法退出" << endl;
		}
		auto it = bookList.begin();
		while (it != bookList.end())
		{
			string buffer;
			//格式化书籍信息并保存在buffer中
			buffer += (it->second._name + " " + to_string(it->second._total) + " " + to_string(it->second._borrowed));

			fout << buffer << endl;//写入文件
			++it;
		}
		//cout << "保存成功" << endl;
		fout.close();
		//保存借书表
		fout.open("借书信息.txt", ios::out);
		if (!fout.is_open())
		{
			cout << "借书信息保存失败，无法退出" << endl;
		}
		auto it1 = borrowList.begin();
		while (it1 != borrowList.end())
		{
			string buffer;
			//格式化借书表并保存在buffer中
			buffer += (it1->_bookName + " " + it1->_personName + " " + it1->_borrowDate.toString() + " " + it1->_returnDate.toString());

			fout << buffer << endl;//写入文件
			++it1;
		}
		fout.close();
	}
	//新增图书
	bool addBook()
	{
		string name;
		cout << "请输入书名：";
		cin >> name;
		auto res = bookList.find(name);
		if (res == bookList.end())//之前没有
		{
			Book book(name, 1 , 0);
			auto ret = bookList.insert({ name, book });
			return ret.second;
		}
		else//之前存在这本书
		{
			bookList[name]._total++;
			return true;
		}
	}
	//打印所有图书信息
	void printBooksName()
	{
		printf("|书名                |藏书数 |借出数 |剩余数 |\n");
		auto it = bookList.begin();
		while (it != bookList.end())
		{
			printf("|%-20s|%7d|%7d|%7d|\n", \
				it->second._name.c_str(), it->second._total, it->second._borrowed, it->second._total - it->second._borrowed);
			++it;
		}
	}
	//根据书名检索书刊
	void findByName()
	{
		string name;
		cout << "请输入需要查询的书名:";
		cin >> name;
		auto ret = bookList.find(name);
		if (ret == bookList.end())
		{
			cout << "没有找到这本书的相关信息" << endl;
		}
		else
		{
			cout << "查询到该书" << endl;
			ret->second.Print();
		}
	}
	void borrowBook()//借书
	{
		//cout << "借书" << endl;
		string bookName;
		cout << "请输入要借阅的书籍名称:";
		cin >> bookName;
		auto ret = bookList.find(bookName);
		if (ret == bookList.end())
		{
			cout << "不存在该书" << endl;
			return;
		}
		if (ret->second._total - ret->second._borrowed == 0)
		{
			cout << "该书已经全部被借走，无法借阅" << endl;
			return;
		}
		BorrowInfo info(bookName, username);
		borrowList.push_back(info);
		ret->second._borrowed++;
		cout << "借书成功 " << username << " 借阅 " << bookName << endl;
		cout << "借书时间:" << info._borrowDate << " 最晚还书时间:" << info._returnDate << endl;

	}
	void findBorrowInfo()//查询读者的借阅信息
	{
		//cout << "查询读者的借阅信息" << endl;
		string readerName;
		cout << "请输入要查找的读者姓名:";
		cin >> readerName;
		//组织借阅信息，按照姓名分类
		map<string, list<BorrowInfo>> Info;
		auto it = borrowList.begin();
		while (it != borrowList.end())
		{
			auto ret = Info.find(readerName);
			if (ret == Info.end())//没有找到对用的用户的借阅信息
			{
				list<BorrowInfo> tmp;
				tmp.push_back(*it);
				Info.insert(make_pair(readerName, tmp));
			}
			else//找到了
			{
				ret->second.push_back(*it);
			}
			++it;
		}
		//查找指定姓名的借阅信息
		auto ret = Info.find(readerName);
		if (ret == Info.end())
		{
			cout << "无该用户的借阅信息" << endl;
			return;
		}
		cout << "借阅者姓名:" << readerName << endl;
		cout << "借阅书籍清单:" << endl;
		auto it1 = ret->second.begin();
		printf("  |借阅人姓名  |书名                |借书日期      |还书日期      |\n");
		while (it1 != ret->second.end())
		{
			string s1 = it1->_borrowDate.json();
			string s2 = it1->_returnDate.json();
			printf("  |%-12s|%-20s|%s|%s|\n", it1->_personName.c_str(), it1->_bookName.c_str(), s1.c_str(), s2.c_str());
			++it1;
		}
	}
	void returnBook()//还书
	{
		//cout << "还书" << endl;
		string userName;
		string bookName;
		cout << "请输入还书人姓名:";
		cin >> userName;
		cout << "请输入要还书名:";
		cin >> bookName;
		auto it = borrowList.begin();
		while (it != borrowList.end())
		{
			if (userName == it->_personName && bookName == it->_bookName)
			{
				auto ret = bookList.find(bookName);
				if (ret != bookList.end())
				{
					ret->second._borrowed--;
					it = borrowList.erase(it);
					cout << "还书成功" << endl;
					return;
				}
				else
				{
					cout << "没有收录该书" << endl;
				}
			}
		}
		cout << "不存在该项借书记录" << endl;
	}
private:
	map<string, Book> bookList;
	list<BorrowInfo> borrowList;
};
