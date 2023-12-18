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
		cout << "  ����:" << _name << endl;
		cout << "  ������:" << _total << "��" << endl;
		cout << "  �ѽ��:" << _borrowed << "��" << endl;
		cout << "  ʣ��:" << _total - _borrowed << "��" << endl;
	}
	string _name;  // ����
	int _borrowed; // ����������
	int _total;    // �����������
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
	string _bookName;   // ����
	string _personName; // ����������
	Date _borrowDate;   // ��������
	Date _returnDate;   // ��ٻ�������
};

class BookList
{
public:
	//���ļ��м��������Ϣ
	void loadMessage()
	{
		ifstream fin;
		char buffer[1024] = { 0 };
		//�������б�
		fin.open("�鼮��Ϣ.txt", ios::in);
		if (!fin.is_open())
		{
			cout << "�����鼮��Ϣʧ�ܣ������˳�" << endl;
			exit(-1);
		}
		while (fin.getline(buffer, sizeof(buffer)))
		{
			//�ַ�����ʽȻ����book����
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
				bookList.insert(make_pair(tmpV[0], tmp)); //��book������뵽bookList��
			}
		}
		fin.close();
		//���ؽ����
		fin.open("������Ϣ.txt", ios::in);
		if (!fin.is_open())
		{
			cout << "���������Ϣʧ�ܣ������˳�" << endl;
			exit(-1);
		}
		while (fin.getline(buffer, sizeof(buffer)))
		{
			//�ַ�����ʽȻ����borrowinfo����
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
	//������Ϣ���ļ���
	void saveMessage()
	{
		ofstream fout;
		//�����鼮��Ϣ
		fout.open("�鼮��Ϣ.txt", ios::out);
		if (!fout.is_open())
		{
			cout << "�ļ�����ʧ�ܣ��޷��˳�" << endl;
		}
		auto it = bookList.begin();
		while (it != bookList.end())
		{
			string buffer;
			//��ʽ���鼮��Ϣ��������buffer��
			buffer += (it->second._name + " " + to_string(it->second._total) + " " + to_string(it->second._borrowed));

			fout << buffer << endl;//д���ļ�
			++it;
		}
		//cout << "����ɹ�" << endl;
		fout.close();
		//��������
		fout.open("������Ϣ.txt", ios::out);
		if (!fout.is_open())
		{
			cout << "������Ϣ����ʧ�ܣ��޷��˳�" << endl;
		}
		auto it1 = borrowList.begin();
		while (it1 != borrowList.end())
		{
			string buffer;
			//��ʽ�������������buffer��
			buffer += (it1->_bookName + " " + it1->_personName + " " + it1->_borrowDate.toString() + " " + it1->_returnDate.toString());

			fout << buffer << endl;//д���ļ�
			++it1;
		}
		fout.close();
	}
	//����ͼ��
	bool addBook()
	{
		string name;
		cout << "������������";
		cin >> name;
		auto res = bookList.find(name);
		if (res == bookList.end())//֮ǰû��
		{
			Book book(name, 1 , 0);
			auto ret = bookList.insert({ name, book });
			return ret.second;
		}
		else//֮ǰ�����Ȿ��
		{
			bookList[name]._total++;
			return true;
		}
	}
	//��ӡ����ͼ����Ϣ
	void printBooksName()
	{
		printf("|����                |������ |����� |ʣ���� |\n");
		auto it = bookList.begin();
		while (it != bookList.end())
		{
			printf("|%-20s|%7d|%7d|%7d|\n", \
				it->second._name.c_str(), it->second._total, it->second._borrowed, it->second._total - it->second._borrowed);
			++it;
		}
	}
	//�������������鿯
	void findByName()
	{
		string name;
		cout << "��������Ҫ��ѯ������:";
		cin >> name;
		auto ret = bookList.find(name);
		if (ret == bookList.end())
		{
			cout << "û���ҵ��Ȿ��������Ϣ" << endl;
		}
		else
		{
			cout << "��ѯ������" << endl;
			ret->second.Print();
		}
	}
	void borrowBook()//����
	{
		//cout << "����" << endl;
		string bookName;
		cout << "������Ҫ���ĵ��鼮����:";
		cin >> bookName;
		auto ret = bookList.find(bookName);
		if (ret == bookList.end())
		{
			cout << "�����ڸ���" << endl;
			return;
		}
		if (ret->second._total - ret->second._borrowed == 0)
		{
			cout << "�����Ѿ�ȫ�������ߣ��޷�����" << endl;
			return;
		}
		BorrowInfo info(bookName, username);
		borrowList.push_back(info);
		ret->second._borrowed++;
		cout << "����ɹ� " << username << " ���� " << bookName << endl;
		cout << "����ʱ��:" << info._borrowDate << " ������ʱ��:" << info._returnDate << endl;

	}
	void findBorrowInfo()//��ѯ���ߵĽ�����Ϣ
	{
		//cout << "��ѯ���ߵĽ�����Ϣ" << endl;
		string readerName;
		cout << "������Ҫ���ҵĶ�������:";
		cin >> readerName;
		//��֯������Ϣ��������������
		map<string, list<BorrowInfo>> Info;
		auto it = borrowList.begin();
		while (it != borrowList.end())
		{
			auto ret = Info.find(readerName);
			if (ret == Info.end())//û���ҵ����õ��û��Ľ�����Ϣ
			{
				list<BorrowInfo> tmp;
				tmp.push_back(*it);
				Info.insert(make_pair(readerName, tmp));
			}
			else//�ҵ���
			{
				ret->second.push_back(*it);
			}
			++it;
		}
		//����ָ�������Ľ�����Ϣ
		auto ret = Info.find(readerName);
		if (ret == Info.end())
		{
			cout << "�޸��û��Ľ�����Ϣ" << endl;
			return;
		}
		cout << "����������:" << readerName << endl;
		cout << "�����鼮�嵥:" << endl;
		auto it1 = ret->second.begin();
		printf("  |����������  |����                |��������      |��������      |\n");
		while (it1 != ret->second.end())
		{
			string s1 = it1->_borrowDate.json();
			string s2 = it1->_returnDate.json();
			printf("  |%-12s|%-20s|%s|%s|\n", it1->_personName.c_str(), it1->_bookName.c_str(), s1.c_str(), s2.c_str());
			++it1;
		}
	}
	void returnBook()//����
	{
		//cout << "����" << endl;
		string userName;
		string bookName;
		cout << "�����뻹��������:";
		cin >> userName;
		cout << "������Ҫ������:";
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
					cout << "����ɹ�" << endl;
					return;
				}
				else
				{
					cout << "û����¼����" << endl;
				}
			}
		}
		cout << "�����ڸ�������¼" << endl;
	}
private:
	map<string, Book> bookList;
	list<BorrowInfo> borrowList;
};
