#ifndef STRING_H
#define STRING_H
#pragma once
#include <iostream>
using namespace std;


class String
{
	friend istream &operator >> (istream &in, String &i);
	friend ostream &operator<<(ostream &out, const String &o);

public:
	String(const char *strinki);
	String(const char *strinki, int length);
	String(int times, const char *strinki);
	String(const String &c);
	String();
	~String();
	operator const char*();
	String &operator++(); //pre
	String operator++(int); //post	
	char &operator[](int i);
	const char& operator[](int i) const;
	const String& operator=(const String &copied);
	String operator+(const String &addedString) const;
	void list();
	static int getCount();
private:
	char *c_string;
	static int Count;
	static const int MAX_STRING_LENGTH = 254;
};
#endif // !STRING_H