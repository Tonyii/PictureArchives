#include "stdafx.h"
#include "String.h"

int String::Count = 0;
String::String(const char *strinki)
{
	if (strlen(strinki) >= MAX_STRING_LENGTH) {
		char newStrinki[MAX_STRING_LENGTH + 1];
		for (int i = 0; i < MAX_STRING_LENGTH + 1; i++) {
			newStrinki[i] = strinki[i];
		}
		newStrinki[MAX_STRING_LENGTH] = 0;
		c_string = new char[strlen(newStrinki) + 1];
		strcpy(c_string, newStrinki);
	}
	else {
		c_string = new char[strlen(strinki) + 1];
		strcpy(c_string, strinki);
	}
	Count++;
}

String::String(const char * strinki, int length)
{
	c_string = new char[length + 1];
	strcpy(c_string, strinki);
}


String::String() {
	c_string = new char[1];
	c_string[0] = 0;
	Count++;
}

String::String(int times, const char * strinki)
{
	if (strlen(strinki) >= MAX_STRING_LENGTH) {
		char newStrinki[MAX_STRING_LENGTH + 1];
		for (int i = 0; i < MAX_STRING_LENGTH + 1; i++) {
			newStrinki[i] = strinki[i];
		}
		newStrinki[MAX_STRING_LENGTH] = 0;
		c_string = new char[strlen(newStrinki) + 1];
		strcpy(c_string, newStrinki);
	}
	else {
		c_string = new char[strlen(strinki) * times + 1];
		strcpy(c_string, strinki);
		for (int i = 0; i < times - 1; i++) {
			strcat(c_string, strinki);
		}
	}
	Count++;
}

/*Copy constructor*/
String::String(const String &c) {
	c_string = new char[strlen(c.c_string) + 1];
	strcpy(c_string, c.c_string);
	Count++;
}

/*Destructor*/
String::~String()
{
	delete c_string;
	Count--;
}


String::operator const char*()
{
	return c_string;
}


ostream & operator<<(ostream &out, const String &o) {
	out << o.c_string;
	return out;
}

istream &operator >> (istream &in, String &i) {
	in >> i.c_string;
	return in;
}

String String::operator+(const String &addedString) const {

	int length = strlen(c_string) + strlen(addedString.c_string) + 2;
	char *c_string2;
	c_string2 = new char[length];
	strcpy(c_string2, c_string);
	strcat(c_string2, addedString.c_string);
	String both(c_string2);
	delete c_string2;
	return both;
}

String String::operator++(int)	//POST increment
{
	String oldString = *this;
	String X("X");
	*this = *this + X;
	return oldString;
}

String & String::operator++()		//PRE increment
{
	String X("X");
	*this = *this + X;
	return *this;
}

char & String::operator[](int i)
{
	if (0 <= i && i < strlen(c_string)) {
		return c_string[i];
	}
	return c_string[0];
}

const char & String::operator[](int i) const
{
		return c_string[i];
}

const String& String::operator=(const String &copied) {
	if (this != &copied) {	//if not same object
		delete c_string;
		c_string = new char[strlen(copied.c_string) + 1];
		strcpy(c_string, copied.c_string);
	}
	return *this;
}

int String::getCount() {
	return Count;
}

