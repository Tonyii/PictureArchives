#include "stdafx.h"
#include "MenuUi.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27
#define CURSOR "=>"
#define ENTER 13
#define Y 121
#define N 110
#define INIT 0
#define SAVEDISK 1
#define LOADDISK 2
#define NEWPIC 3
#define DELPIC 4
#define PRINTMINPEOPLE 5
#define PRINTALL 6

MenuUi::MenuUi(int yCommands) : save1("session1"), runMenu(true), picMenu(false), x(0, 2), y(0, yCommands), yList(yCommands + 1), xPrev(0, 2), yPrev(0, yCommands), lastAction()
{
	for (int i = 0; i == yCommands; i++) {	//make strings that can hold the "POINTER"
		yList[i] = string("", 3);
	}
	upperLayout = ("\n###################################################################\n                   Welcome to Picture software\n###################################################################\n\n");
}


MenuUi::~MenuUi()
{
	deleteArchive();
}

void MenuUi::start()
{
	//for testing:
	for (int i = 0; i < 10; ++i) {
		string file = "testfile.jpg";
		Picture p(file, "this is a description of this picture with details of the image", "Suomi, Tampere", i);
		archive.push_back(p);
	}
	//
	/*this sets the size of command line*/
	system("MODE 75,50");

	run();
	while (!areYouSure("All unsaved images will be lost. \nAre you sure you want to exit")) {
		run();
	}
}

void MenuUi::run()
{
	while (runMenu) {
		y.setLimit(yList.size() - 1);
		yList[yPrev] = "";	//remove mark from previous
		yList[y] = CURSOR;	//counter operator int

		system("CLS");		//this clears screen
		cout << upperLayout << endl;	//print upper layout
		cout << left << setw(23) << "Pictures at the moment: " << setw(4) << Picture::getCount() << "last action:" << lastAction << "\n\n   Commands:\n";
		cout << left << setw(3) << yList[0] << "initialize (clear all)\n" <<
			setw(3) << yList[1] << "save pic records to disk\n" <<
			setw(3) << yList[2] << "read pic records from disk\n" <<
			setw(3) << yList[3] << "add pic\n" <<
			setw(3) << yList[4] << "remove pic\n" <<
			setw(3) << yList[5] << "print report : pics with user def min people\n" <<
			setw(3) << yList[6] << "print report : all pics, no people is marked *\n" << endl;
		takeInput();
	}
}

void MenuUi::takeInput()
{
	int keyPressed = getch();

	switch (keyPressed) {
	case UP:
		yPrev = y--;
		break;
	case DOWN:
		yPrev = y++;
		break;
	case LEFT:
		break;
	case RIGHT:
		break;
	case ESC:	//Exits
		if (picMenu) picMenu = false;
		else runMenu = false;
		break;
	case ENTER:
		system("CLS"); //clear screen
		if (picMenu) deletePic(y);
		else {
			lastAction = select(y); //saves the lastAction string and calls select
			cout << "\nPress any key to continue";
			int c = getch();	//waits for user input
		}
		break;
	}
}

string MenuUi::select(int selection)
{
	cout << upperLayout;

	switch (selection) {
	case INIT:
		if (!archive.empty() && areYouSure("This will erase all images in current session\nAre you sure"))	deleteArchive();
		changes = "everything cleared";
		break;
	case SAVEDISK:
		if (areYouSure("This will overwrite previous saves")) save1.writeTo(archive);
		changes = "records saved";
		break;
	case LOADDISK:
		if (areYouSure("This will load over current images")) save1.loadTo(archive);
		changes = "records loaded";
		break;
	case NEWPIC:
		newPic();
		changes = "Picture added";
		break;
	case DELPIC:
		delPicMenu();
		changes = "Picture deleted";
		break;
	case PRINTMINPEOPLE:
		printPeople();
		changes = "Report given";
		break;
	case PRINTALL:
		printAll();
		changes = "Report given";
		break;
	}
	return changes;
}

void MenuUi::printPeople()
{
	/*check if there are pictures*/
	if (archive.empty()) {
		cout << "\nThere are no pictures" << endl;
		return;
	}
	int min;
	
	cout << "Define the minimum persons in the picture: ";
	cin >> min;
	while (cin.fail() || min == NULL || min < 0) {
		cin.clear();
		cin.ignore(255, '\n');
		cout << "NOT GOOD: please use a number between 0 and 999.\nmin number of people in image[0-999]: ";
		cin >> min;
	}
	cin.ignore();
	cout << endl;
	
	/*print only pictures with enough people*/
	for (auto &pic : archive) {
		if (pic.getPeople() >= min) cout << pic << "\n\n";
	}
}


void MenuUi::printAll()
{
	cout << left << setw(3) << "" << setw(20) << "Filename" << setw(20) << "Location" << setw(20) << "Persons" << "* if 0" << "\n" << "   Description" << endl;
	for (int i = 0; i < 68; ++i) { cout << "#"; }
	cout << endl << endl;
	/*Check if there are pictures*/
	if (archive.empty()) {
		cout << "\nThere are no pictures" << endl;
		return;
	}
	for (auto &pic : archive) {
		char star = ' ';
		if (pic.getPeople() == 0) star = '*';
		cout << pic << "  " << star << "\n\n";
	}
	cout << endl;
}

void MenuUi::newPic()
{
	string filename, description, loc;
	int nrOfPeople = 0;
	bool loop = true;

	/*ask for filename*/
	cout << "Add new picture to the archives. Give essential information:\n\nfilename[20 chars]: ";
	getline(cin, filename);
	while (!inputlength(filename, 20, false)) getline(cin, filename);

	/*ask for location*/
	cout << "\n\nlocation[20 chars]: ";
	getline(cin, loc);
	while (!inputlength(loc, 20)) getline(cin, loc);

	/*ask for description*/
	cout << "\n\ndescription[60 chars]: ";
	getline(cin, description);
	while (!inputlength(description, 60)) getline(cin, description);

	/*ask for amount of people in picture*/
	cout << "\n\nnumber of people in image[0-999]: ";
	cin >> nrOfPeople;
	while (cin.fail() || nrOfPeople == NULL || nrOfPeople < 0) {
		cin.clear();
		cin.ignore(255, '\n');
		cout << "NOT GOOD: please use a number between 0 and 999.\nnumber of people in image[0-999]: ";
		cin >> nrOfPeople;
	}
	cin.ignore();

	Picture p(filename, description, loc, nrOfPeople);
	archive.push_back(p);
	return;
}

void MenuUi::delPicMenu() {

	yList[yPrev] = "";					//remove cursor from last menu item 
	yList[y] = "";
	LimitedCounter mainY = y;			//to return cursor when returning back to main menu
	yPrev.reset();
	y.reset();							//set y cursor to 0
	picMenu = true;

	while (picMenu) {
		/*check if there are pictures*/
		if (archive.empty()) {
			cout << "\nThere are no pictures" << endl;
			picMenu = false;
			y = mainY;
			return;
		}
		y.setLimit(archive.size() - 1);
		yPrev.setLimit(archive.size() - 1); //to avoid referencing old out of range item
		archive[yPrev] = "";			//remove cursor from previous selection
		archive[y] = CURSOR;			//operator=
		system("CLS");					//clear screen
		cout << upperLayout << endl;	//print upper layout
		cout << left << setw(40) << "Pictures at the moment: " << Picture::getCount() << "\nSelect a picture to delete" << '\n' << endl;
		for (auto &pic : archive) {
			cout << pic << "\n\n";				//operator<<
		}
		takeInput();
	}
	archive[y] = "";
	y = mainY;
}
//
/*---------------THESE FUNCTIONS ARE FOR CHECKING--------------------------*/
//
bool MenuUi::areYouSure(string question)
{
	cout << question << "? (y = yes / n = no)" << endl;
	int input;
	do {
		input = getch();
		if (input == Y) return true;
		else if (input == N) return false;
	} while (true);
}

bool MenuUi::inputlength(string &input, int maxLen, bool canBeEmpty)
{
	if (input.size() > maxLen) {
		cout << "NOT GOOD: Maximun characters allowed is " << maxLen << "\nTry again: ";
		return false;
	}
	else if (canBeEmpty == false && input == "") cout << "NOT GOOD: This cant be empty" << "\nTry again: ";
	else return true;
}

void MenuUi::deletePic(int i) {
	cout << upperLayout;
	if (areYouSure("Are you sure want to delete this picture")) { //ask yes or no
		if (i != (archive.size() - 1)) {
			archive.erase(archive.begin() + i);
			return;
		}
		else {
			archive.erase(archive.end() - 1);
		}
	}
	else return;
}

void MenuUi::deleteArchive()
{
	/*Goes through vector calling destructors, for safety*/
	for (vector<Picture>::iterator it = archive.begin(); it != archive.end(); it = archive.begin()) {
		archive.erase(it);
	}
}
