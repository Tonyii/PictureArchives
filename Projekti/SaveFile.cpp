#include "stdafx.h"
#include "SaveFile.h"
#include <memory>


SaveFile::SaveFile(string name_, bool makeNew) : name(name_)
{
}


SaveFile::~SaveFile()
{
}

void SaveFile::writeTo(vector<Picture> &v)
{
	ofstream file(name);
	if (file.is_open()) {
		for (auto &pic : v) {
			file << pic << endl;
		}
		file.close();
	}
	else cout << "file did not open";
}

void SaveFile::loadTo(vector<Picture> &v)
{
	string line, filename, location;
	int nrOfPeople;
	ifstream file(name);
	v.clear();
	if (file.is_open()) {
		while (getline(file, line)) { //get first line
			filename = line.substr(3, 20); //20 chars
			location = line.substr(23, 20); //20 chars
			nrOfPeople = stoi(line.substr(43, 11)); //11 chars
			/*get description line*/
			getline(file, line);
			/*add new Picture with parsed parameters from input line*/
			v.push_back(Picture(filename, line.substr(3, 60), location, nrOfPeople)); //60chars of description
		}
		file.close();
	}
	else cout << "file did not open";
}


ostream & operator<<(ostream & out, vector<Picture>& o)
{

	return out;
}
/*
ostream & operator<<(ostream & out, const SaveFile & o)
{
	string line, filename, location;
	int nrOfPeople;
	ifstream file("name");
	if (file.is_open()) {
		while (getline(file, line)) { //get first line
			filename = line.substr(3, 20); //20 chars
			location = line.substr(23, 20); //20 chars
			nrOfPeople = stoi(line.substr(43, 11)); //11 chars
			getline(file, line);
			out << (Picture(filename, line.substr(3, 60), location, nrOfPeople)); //60chars of description
		}
		file.close();
		return out;
	}
	else cout << "file did not open";
	return out;
}

istream & operator >> (istream & in, SaveFile & i)
{
	ofstream file;
	file.open(i.name);
	file << in;
}*/
