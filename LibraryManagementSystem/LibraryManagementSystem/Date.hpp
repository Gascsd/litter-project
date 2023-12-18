#pragma once

class Date
{
	friend ostream& operator<<(ostream& _cout, Date& d);
	friend istream& operator>>(istream& _cin, Date& d);
public:
	Date(int year = 1970, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}
	//�ж��Ƿ�Ϊ����
	bool is_leap_year(int year)
	{
		return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	}
	// ��ȡĳ��ĳ�µ�����
	int GetMonthDay(int year, int month)
	{
		static int MonthDay[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month == 2)//�ж��Ƿ�Ϊ�����2��
		{
			if (is_leap_year(year))
			{
				return 29;
			}
		}
		else
		{
			return MonthDay[month];
		}
	}
	// ����+=����
	Date& operator+=(int day)
	{
		_day += day;
		while (_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			_month++;
			if (_month == 13)
			{
				_year++;
				_month = 1;
			}
		}
		return *this;
	}
	// ����+����
	Date operator+(int day)
	{
		Date ret(*this);
		ret += day;
		return ret;
	}
	// ����-����
	Date operator-(int day)
	{
		Date ret(*this);
		ret -= day;
		return ret;
	}
	// ����-=����
	Date& operator-=(int day)
	{
		while (_day < day)
		{
			day -= _day;
			_month--;
			if (_month == 0)
			{
				_year--;
				_month = 12;
			}
			_day = GetMonthDay(_year, _month);
		}
		_day -= day;
		return *this;
	}
	bool operator==(const Date& d)
	{
		return _year == d._year && _month == d._month && _day == d._day;
	}
	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}
	Date stringtToDate(string d)
	{
		_year = stoi(d.substr(0, 4));
		_month = stoi(d.substr(4, 2));
		_day = stoi(d.substr(6, 2));
		return *this;
	}
	string toString()//���ڸ�ʽ��Ϊ�ַ���ע�����ڴ�ǰ���� 0000-00-00
	{
		string yearStr = to_string(_year);
		string monthStr = to_string(_month);
		string dayStr = to_string(_day);
		if(_month < 10)
			monthStr = "0" + monthStr; 
		if(_day < 10)
			dayStr = "0" + dayStr;
		return (yearStr + monthStr + dayStr);
	}
	string json()
	{
		string ret;
		string yearStr = to_string(_year);
		string monthStr = to_string(_month);
		string dayStr = to_string(_day);
		if (_month < 10)
			monthStr = "0" + monthStr;
		if (_day < 10)
			dayStr = "0" + dayStr;
		return (yearStr + "��" + monthStr + "��" + dayStr + "��");
	}
private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& _cout, Date& d)
{
	_cout << d._year << "��" << d._month << "��" << d._day << "��";
	return _cout;
}

istream& operator>>(istream& _cin, Date& d)
{
	cin >> d._year >> d._month >> d._day;
	return _cin;
}