#pragma once
#include <string>
#include <iostream>
using namespace std;

class Picture
{
	friend ostream &operator<<(ostream &out, const Picture &o);
public:
	Picture();
	Picture(string filename_, string description_,string location_, int nrOfPeople_);
	Picture(const Picture &c);
	~Picture();

	const Picture& operator=(const string &pointy); //for printing cursor
	int getPeople();
	static int getCount();

private:
	string cursor;
	string filename;
	string description;
	string location;
	int nrOfPeople;

	static int pictureCount;
};

