#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <iostream>
#include <cstdio>
#include <ostream>
#include <istream>
#include <assert.h>
namespace bit {
	class string {

		//friend ostream& operator<<(ostream& _cout, const string& s);
		//friend istream& operator>>(istream& _cin, string& s);

	public:

		typedef char* iterator;

	public:

		string(const char* str = ""):
		_size(strlen(str)),
		_capacity(_size){
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		string(const string& s) :
			_size(strlen(s.c_str())),
			_capacity(_size) {
			_str = new char[_capacity + 1];
			strcpy(_str, s.c_str());
		}
		string& operator=(const string& s);
		~string() {
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}

		//////////////////////////////////////////////////////////////
		// iterator

		iterator begin() {
			return _str;
		}
		iterator end() {
			return _str+_size;
		}

		/////////////////////////////////////////////////////////////
		// modify

		void push_back(char c) {
			if (_capacity == _size) {
				reserve(_capacity == 0 ? 4 : 2 * _capacity);
			}
			_str[_size] = c;
			_str[_size + 1] = '/0';
			_size++;
		}
		string& operator+=(char c) {
			push_back(c);
			return *this;
		}
		void append(const char* str) {
			size_t len = strlen(str);
			if (_size + len > _capacity) {
				reserve(_size + len);
			}
			strcpy(_str + _size, str);
			_size += len;
		}
		string& operator+=(const char* str) {
			append(str);
			return *this;
		}
		void clear() {
			_str[0] = '/0';
			_size = 0;
		}
		void swap(string& s);
		const char* c_str()const;

		/////////////////////////////////////////////////////////////
		// capacity

		size_t size()const {
			return _size;
		}
		size_t capacity()const {
			return _capacity;
		}
		bool empty()const {
			return !_size;
		}
		void resize(size_t n, char c = '\0') {
			assert(n > _size);
			reserve(n);
			for (int i = _size; i < n; i++) {
				_str[i] = c;
			}
			_size = n;
			_str[_size] = '/0';
		}
		void reserve(size_t n) {
			if (n > _capacity) {
				char* tmp = new char[n + 1];
				_str = strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}

		}

		/////////////////////////////////////////////////////////////
		// access

		char& operator[](size_t index) {
			return _str[index];
		}
		const char& operator[](size_t index)const {
			return _str[index];
		}

		/////////////////////////////////////////////////////////////
		//relational operators

		bool operator<(const string& s) {
			return strcmp(this->_str,s.c_str())<0;
		}
		bool operator<=(const string& s) {
			return this->_str < s.c_str() || this->_str == s.c_str();
		}
		bool operator>(const string& s) {
			return !(this->_str < s.c_str() || this->_str == s.c_str());
		}
		bool operator>=(const string& s) {
			return this->_str > s.c_str() || this->_str == s.c_str();
		}
		bool operator==(const string& s) {
			return strcmp(this->_str, s.c_str()) == 0;
		}
		bool operator!=(const string& s) {
			return !(this->_str == s.c_str());
		}

		// 返回c在string中第一次出现的位置
		size_t find(char c, size_t pos = 0) const {
			assert(pos < _size);
			assert(pos >= 0);
			while (pos < _size) {
				if (_str[pos] == c) {
					return pos;
				}
				pos++;
			}
			return -1;
		}

		// 返回子串s在string中第一次出现的位置
		size_t find(const char* s, size_t pos = 0) const {
			const char* p = strstr(_str + pos, s);
			if (p)
			{
				return p - _str;
			}
			else
			{
				return -1;
			}
		}

		// 在pos位置上插入字符c/字符串str，并返回该字符的位置
		string& insert(size_t pos, char c) {
			assert(pos <= _size);
			assert(pos >= 0);
			if (_capacity == _size) {
				reserve(_capacity == 0 ? 4 : 2 * _capacity);
			}
			for (int i = _size; i >= (int)pos; i--) {
				_str[i] = _str[i - 1];
			}
			_str[pos ] = c;
			_size++;
			_str[_size] = '/0';
			return *this;
		}
		string& insert(size_t pos, const char* str) {
			int len = strlen(str);
			if (len + _size > _capacity) {
				reserve(_size + len);
			}
			for (int i = _size; i >= (int)pos; i--) {
				_str[i+len] = _str[i - 1];
			}
			strcpy(_str + pos, str);
			_size+=len;
			
			return *this;
		}

		// 删除pos位置上的元素，并返回该元素的下一个位置
		string& erase(size_t pos, size_t len) {
			assert(pos < _size);
			assert(pos >= 0);
			if (pos + len > _size) {
				_str[pos] = '/0';
			}
			else {
				int end = pos + len;
				for (int i = end; i <= _size; i++) {
					_str[pos] = _str[i];
					pos++;

				}
				_size -= len;
			}
			return *this;
		}

	private:

		char* _str;
		size_t _capacity;
		size_t _size;

	};
	/*ostream& operator <<(ostream& _cout, const string& s) {

	}
	istream& operator >>(istream& _cin, string& s) {
		
	}*/
	void t1() {
		string("123");
	}

}