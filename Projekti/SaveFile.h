#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "SaveFile.h"
#include "Picture.h"
#include <string>
using namespace std;

class SaveFile
{
	friend ostream &operator<<(ostream &out, vector<Picture> &o);
/*	friend ostream &operator<<(ostream &out, const SaveFile &o);
	friend istream &operator >> (istream &in, SaveFile &i);*/
public:
	SaveFile(string name_, bool makeNew = false);
	~SaveFile();
	void writeTo(vector<Picture> &v);
	void loadTo(vector<Picture> &v);
private:
	string name;
};

