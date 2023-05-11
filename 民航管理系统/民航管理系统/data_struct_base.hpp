#pragma once
#include <utility>
#include <iostream>
#include<assert.h>
using namespace std;

namespace my
{
	//vector
	template<class T>
	class vector
	{
	public:
		// Vector的迭代器是一个原生指针
		typedef T* iterator;
		typedef const T* const_iterator;
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator cbegin() const
		{
			return _start;
		}
		const_iterator cend() const
		{
			return _finish;
		}
		// construct and destroy
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{}
		vector(int n, const T& value = T())
		{
			reserve(n);
			for (int i = 0; i < n; ++i)
			{
				push_back(value);
			}
		}
		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		vector(const vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			vector<T> tmp(v.cbegin(), v.cend());
			swap(tmp);
		}
		vector<T>& operator= (vector<T> v)
		{
			swap(v);
			return *this;
		}
		~vector()
		{
			delete[] _start;
			_start = _finish = _endOfStorage = nullptr;
		}
		// capacity
		size_t size() const
		{
			return _finish - _start;
		}
		size_t capacity() const
		{
			return _endOfStorage - _start;
		}
		bool empty() const
		{
			return _start == _finish;
		}
		void reserve(size_t n)
		{
			if (capacity() < n)
			{
				size_t oldSize = size();
				T* tmp = new T[n];
				if (_start)
				{
					for (size_t i = 0; i < oldSize; ++i)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + oldSize;
				_endOfStorage = _start + n;
			}
		}
		void resize(size_t n, const T& value = T())
		{
			if (n > capacity())
			{
				reserve(n);
			}
			if (n > size())
			{
				while (_finish != _start + n)
				{
					*_finish = value;
					++_finish;
				}
			}
			else
			{
				_finish = _start + n;
			}
		}
		///////access///////////////////////////////
		T& operator[](size_t pos)
		{
			assert(pos < size());
			return _start[pos];
		}
		const T& operator[](size_t pos)const
		{
			assert(pos < size());
			return _start[pos];
		}
		///////////////modify/////////////////////////////
		void push_back(const T& x)
		{
			if (_finish == _endOfStorage)
			{
				size_t newCapacity = capacity() == 0 ? 4 : 2 * capacity();
				reserve(newCapacity);
			}
			*_finish = x;
			++_finish;
		}
		void pop_back()
		{
			assert(!empty());
			--_finish;
		}
		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endOfStorage, v._endOfStorage);
		}
		iterator insert(iterator pos, const T& x)
		{
			assert(pos >= _start);
			assert(pos < _finish);
			if (_finish == _endOfStorage)
			{
				size_t len = pos - _start;
				size_t newCapacity = capacity() == 0 ? 4 : 2 * capacity();
				reserve(newCapacity);
				pos = _start + len;
			}
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = x;
			++_finish;
			return pos;
		}
		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);
			assert(!empty());
			iterator begin = pos;
			while (begin < _finish)
			{
				*(begin) = *(begin + 1);
				++begin;
			}
			--_finish;
			return pos;
		}
	private:
		iterator _start; // 指向数据块的开始
		iterator _finish; // 指向有效数据的尾
		iterator _endOfStorage; // 指向存储容量的尾
	};
	
	//list的模拟实现
	template<class T>
	struct __list_node//这是一个list的节点类模板
	{
		__list_node* _prev;
		__list_node* _next;
		T _data;
		__list_node(const T& data = T())//__list_node的默认构造函数
			:_data(data)
			, _prev(nullptr)
			, _next(nullptr)
		{}
	};
	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef __list_node<T> node;//重命名节点类
		typedef __list_iterator<T, Ref, Ptr> Self;
		node* _pnode;//迭代器的成员变量就是结点指针

		__list_iterator(node* p)//迭代器的构造函数
			:_pnode(p)
		{}
		Ptr operator->()
		{
			return &operator*();
		}
		Ref operator*()//重载*，作用是返回指向的节点的元素值
		{
			return _pnode->_data;
		}
		Self& operator++()//重载++，作用是将迭代器自增1
		{
			_pnode = _pnode->_next;
			return *this;
		}
		Self operator++(int)
		{
			Self tmp(*this);
			_pnode = _pnode->_next;
			return tmp;
		}
		Self& operator--()
		{
			_pnode = _pnode->_prev;
			return *this;
		}
		Self operator--(int)
		{
			Self tmp(*this);
			_pnode = _pnode->_prev;
			return tmp;
		}
		bool operator!=(const Self& it)
		{
			return _pnode != it._pnode;
		}
		bool operator==(const Self& it)
		{
			return _pnode == it._pnode;
		}
	};

	template<class T>
	class list//这是一个list类，其中的成员变量只有一个头节点。
	{
		typedef __list_node<T> node;
	public:
		typedef __list_iterator<T, T&, T*> iterator;//普通迭代器
		typedef __list_iterator<T, const T&, const T*> const_iterator;//const迭代器
		iterator begin()
		{
			return _head->_next;
		}
		iterator end()
		{
			return _head;
		}
		const_iterator begin() const
		{
			return _head->_next;
		}
		const_iterator end() const
		{
			return _head;
		}
		void empty_initialize()
		{
			_head = new node(T());
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;
		}
		list()
		{
			empty_initialize();
		}
		list(size_t n, const T& val = T())
		{
			empty_initialize();
			for (size_t i = 0; i < n; ++i)
			{
				push_back(val);
			}
		}
		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			empty_initialize();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);
		}
		list(const list<T>& lt)//现代写法
		{
			empty_initialize();
			list<T> tmp(lt.begin(), lt.end());
			swap(tmp);
		}
		list<T>& operator=(list<T> lt)//现代写法
		{
			swap(lt);
			return *this;
		}
		bool empty()
		{
			return _head->_next == _head;
		}
		void clear()
		{
			while (!empty())
			{
				erase(--end());
			}
		}
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		void push_back(const T& val = T())
		{
			insert(end(), val);
		}
		void push_front(const T& val = T())
		{
			insert(begin(), val);
		}
		iterator insert(iterator pos, const T& val = T())
		{
			node* newnode = new node(val);
			//   prev   newnode   cur
			node* prev = pos._pnode->_prev;
			node* cur = pos._pnode;

			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;

			++_size;
			return iterator(newnode);
		}

		size_t size()
		{
			return _size;
		}
		iterator erase(iterator pos)
		{
			assert(pos != end());
			node* prev = pos._pnode->_prev;
			node* next = pos._pnode->_next;
			//prev    cur    next
			prev->_next = next;
			next->_prev = prev;
			delete pos._pnode;
			--_size;
			return iterator(next);
		}
		void pop_back()
		{
			erase(--end());
		}
		void pop_front()
		{
			erase(begin());
		}
		void resize(size_t n, const T& val = T())
		{
			while (n < size())
			{
				pop_back();
			}
			while (n > size())
			{
				push_back(val);
			}
		}
	private:
		node* _head;
		size_t _size;
	};

}