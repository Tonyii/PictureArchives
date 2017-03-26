#pragma once
#include <iostream>
#include "LimitedCounter.h"
#include "String.h"
#include "SaveFile.h"
#include "Picture.h"
#include <string>
#include <conio.h>
#include <vector>
#include <stdio.h>
#include <iomanip>
#include <algorithm>
#include <memory>
using namespace std;


class MenuUi
{
public:
	MenuUi(int yCommands);
	~MenuUi();
	void start();
	void run();
private:
	SaveFile save1;
	LimitedCounter x, y, xPrev, yPrev;

	bool runMenu;
	bool picMenu;
	vector<string> yList;
	vector<Picture> archive;
	string lastAction;
	string upperLayout;
	string changes;

	void newPic();
	void printAll();
	void deletePic(int i);
	void printPeople();
	void delPicMenu();

	void takeInput();
	void deleteArchive();

	bool inputlength(string &input, int maxLen, bool canBeEmpty = true);
	bool areYouSure(string question);

	string select(int selection);
	
};

