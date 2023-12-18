#define _CRT_SECURE_NO_WARNINGS 1
#include "head.h"
#include "BookList.hpp"
#include "Admin.hpp"



//需要维护一个书籍清单

void loginMenu()
{
	cout << "***************************************" << endl;
	cout << "*************图书馆管理系统************" << endl;
	cout << "***************************************" << endl;
	cout << "*************  0. exit    *************" << endl;
	cout << "*************  1. login   *************" << endl;
	cout << "***************************************" << endl;
}
void readerMenu()
{
	cout << "***************************************" << endl;
	cout << "*************图书馆管理系统************" << endl;
	cout << "************* Reader Menu  ************" << endl;
	cout << "***************************************" << endl;
	cout << "*********  0. 退出                 ****" << endl;
	cout << "*********  1. 查询图书馆藏书信息    ***" << endl;
	cout << "*********  2. 根据书名检索书刊信息  ***" << endl;
	cout << "*********  3. 借书                  ***" << endl;
	cout << "*********  4. 还书                  ***" << endl;
	cout << "***************************************" << endl;
	cout << "***************************************" << endl;
}
void adminMenu()
{
	cout << "***************************************" << endl;
	cout << "*************图书馆管理系统************" << endl;
	cout << "*************  Admin Menu  ************" << endl;
	cout << "***************************************" << endl;
	cout << "*********  0. 退出                 ****" << endl;
	cout << "*********  1. 查询图书馆藏书信息    ***" << endl;
	cout << "*********  2. 存入新书             ****" << endl;
	cout << "*********  3. 根据书名检索书刊信息  ***" << endl;
	cout << "*********  4. 查询读者的借阅信息    ***" << endl;
	cout << "*********  5. 查询读者信息          ***" << endl;
	cout << "*********  6. 查询管理员信息         ***" << endl;
	cout << "***************************************" << endl;
	cout << "***************************************" << endl;
}

void readerMenu(BookList& books, Admin& users)
{
	int input;
	do {
		readerMenu();
		cout << "请输入:>";
		cin >> input;
		switch (input)
		{
		case 0:
			books.saveMessage();
			users.saveMessage();
			cout << "退出..." << endl;
			exit(0);
		case 1:
			cout << "图书信息:" << endl;//查询图书馆藏书信息
			books.printBooksName();
			system("pause");
			system("cls");
			break;
		case 2:
			books.findByName(); //根据书名检索书刊信息
			system("pause");
			system("cls");
			break;
		case 3:
			books.borrowBook();//借书
			system("pause");
			system("cls");
			break;
		case 4:
			books.returnBook();//还书
			system("pause");
			system("cls");
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
			system("pause");
			system("cls");
		}
	} while (input);
}
void adminMenu(BookList& books, Admin& users)
{
	int input;
	do {
		adminMenu();
		cout << "请输入:>";
		cin >> input;
		switch (input)
		{
		case 0:
			books.saveMessage();
			users.saveMessage();
			cout << "退出..." << endl;
			exit(0);
		case 1:
			cout << "图书信息:" << endl;
			books.printBooksName();//查询读者信息
			system("pause");
			system("cls");
			break;
		case 2:
			if (books.addBook())//新增图书
				cout << "新增图书成功" << endl;
			else
				cout << "新增图书失败" << endl;
			system("pause");
			system("cls");
			break;
		case 3:
			books.findByName();//通过书名查询书籍信息
			system("pause");
			system("cls");
			break;
		case 4:
			books.findBorrowInfo();//查询读者的借阅信息
			system("pause");
			system("cls");
			break;
		case 5:
			users.findReader();//查询读者信息
			system("pause");
			system("cls");
			break;
		case 6:
			users.findAdmin();//查询管理员信息
			system("pause");
			system("cls");
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
			system("pause");
			system("cls");
		}
	} while (input);
}

int login(Admin users) //返回身份编码：0 管理员 1 读者
{
	string name;
	string passwd;
	cout << "请输入用户名：";
	cin >> name;
	cout << "请输入密码：";
	cin >> passwd;
	// 0 不存在该用户  1 密码错误 2 管理员 3 读者
	int ret = users.find(name, passwd);
	int res = 2;
	if (ret == 2 || ret == 3)
	{
		cout << "登录成功，欢迎使用图书馆管理系统..." << endl;
		username = name;
	}
	else if (ret == 1)
		cout << "密码错误" << endl;
	else if (ret == 0)
		cout << "不存在该用户" << endl;
	system("pause");
	system("cls");
	return ret - 2;
}

void System()
{
	cout << "正在载入数据..." << endl;
	Sleep(500);
	BookList books;
	books.loadMessage();
	Admin users;
	users.loadMessage();
	cout << "载入数据成功！" << endl;
	int ret = login(users);
	if (ret == 1)
	{
		readerMenu(books, users);
	}
	else if(ret == 0)
	{
		adminMenu(books, users);
	}
}
int main()
{
	int input = 0;
	do {
		loginMenu();
		cout << "请输入:>";
		cin >> input;
		switch (input)
		{
		case 0:
			cout << "退出..." << endl;
			break;
		case 1:
			System();
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
			system("pause");
			system("cls");
		}
	} while (input);
	return 0;
}

//int main()//TEST
//{
//	Admin users;
//	users.addReader();
//	users.saveMessage();
//
//	return 0;
//}