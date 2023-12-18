#pragma once
#include "head.h"

enum Status
{
	READER, // 0����
	ADMIN   // 1ͼ�����Ա
};

struct Person //��
{
	Person() = default;
	Person(const string& stuno, const string& name, const string& passwd, const Status& status = READER, int borrowed = 0) //���캯��
		: _stuno(stuno)
		, _name(name)
		, _passwd(passwd)
		, _status(status)
		, _borrowed(borrowed)
	{

	}

	string _stuno;     //ѧ��
	string _name;      //����
	Status _status;    //���
	string _passwd;    //����
	int _borrowed;     //���������
};

class Admin : Person //����Ա�� 
{
public:
	//Admin() = default;//ǿ��Ĭ�����ɹ��캯��
	Admin() {}//Ĭ�Ϲ���
	
	void loadMessage() // ���ļ��ж�ȡ�û���Ϣ
	{
		ifstream fin;
		fin.open("�û���Ϣ.txt", ios::in);
		if (!fin.is_open())
		{
			cout << "��������ʧ�ܣ������˳�" << endl;
			exit(-1);
		}
		char buffer[1024] = { 0 };
		while (fin.getline(buffer, sizeof(buffer)))
		{
			//��ȡbuffer�е����ݹ���Person����
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

	void saveMessage() // ������Ϣ���ļ���
	{
		ofstream fout;
		fout.open("�û���Ϣ.txt", ios::out);
		if (!fout.is_open())
		{
			cout << "�ļ�����ʧ�ܣ��޷��˳�" << endl;
		}
		//���������Ϣ
		auto it1 = readerList.begin();
		while (it1 != readerList.end())
		{
			string buffer;
			//��ʽ���鼮��Ϣ��������buffer��
			buffer += (it1->_stuno + " " + it1->_name + " " + it1->_passwd + " " + to_string(it1->_status) + " " + to_string(it1->_borrowed));

			fout << buffer << endl;//д���ļ�
			++it1;
		}
		auto it2 = adminList.begin();
		while (it2 != adminList.end())
		{
			string buffer;
			//��ʽ���鼮��Ϣ��������buffer��
			buffer += (it2->_stuno + " " + it2->_name + " " + it2->_passwd + " " + to_string(it2->_status) + " " + to_string(it2->_borrowed));

			fout << buffer << endl;//д���ļ�
			++it2;
		}
		//cout << "����ɹ�" << endl;
	}
	//���Һ˶�
	int find(const string& name, const string passwd) // 0 �����ڸ��û�  1 ������� 2 ����Ա 3 ����
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
	void addAdmin()//���ӹ���Ա
	{
		string name;
		string passwd;
		string stuno;
		cout << "������ѧ��:";
		cin >> stuno;
		cout << "�������û���:";
		cin >> name;
		cout << "����������:";
		cin >> passwd;
		Person p(stuno, name, passwd, ADMIN);
		adminList.push_back(p);
		cout << "��ӹ���Ա�ɹ�" << endl;
	}
	void addReader()//���Ӷ���
	{
		string name;
		string passwd;
		string stuno;
		cout << "������ѧ��:";
		cin >> stuno;
		cout << "�������û���:";
		cin >> name;
		cout << "����������:";
		cin >> passwd;
		Person p(stuno, name, passwd, READER);
		readerList.push_back(p);
		cout << "��Ӷ��߳ɹ�" << endl;
	}
	void findAdmin()//��ѯ����Ա��Ϣ
	{
		int input = 0;
		cout << "��ѯ���й���Ա��Ϣ������1, ��ѯ��������Ա��Ϣ������2:" << endl;
		cin >> input;
		if (input == 1)
		{
			printf("|����Ա����  |����Աѧ��|����\n");
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
			cout << "������Ҫ��ѯ�Ĺ���Ա����:";
			cin >> name;
			auto it = adminList.begin();
			while (it != adminList.end())
			{
				if (it->_name == name)
				{
					printf("|����Ա����  |����Աѧ��|����\n");
					printf("|%-12s|%10s|%s\n", it->_name.c_str(), it->_stuno.c_str(), it->_passwd.c_str());
					return;
				}
				++it;
			}
			cout << "���û�������" << endl;
		}
		else
		{
			cout << "�������" << endl;
		}
	}
	void findReader()//��ѯ������Ϣ
	{
		int input = 0;
		cout << "��ѯ���ж�����Ϣ������1, ��ѯ����������Ϣ������2:" << endl;
		cin >> input;
		if (input == 1)
		{
			printf("|��������    |����ѧ��  |��������|����\n");
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
			cout << "������Ҫ��ѯ�Ķ�������:";
			cin >> name;
			auto it = readerList.begin();
			while (it != readerList.end())
			{
				if (it->_name == name)
				{
					printf("|��������    |����ѧ��  |��������|����\n");
					printf("|%-12s|%10s|%8d|%s\n", it->_name.c_str(), it->_stuno.c_str(), it->_borrowed, it->_passwd.c_str());
					return;
				}
				++it;
			}
			cout << "���û�������" << endl;
		}
		else
		{
			cout << "�������" << endl;
		}
	}
private:
	list<Person> adminList;
	list<Person> readerList;

};