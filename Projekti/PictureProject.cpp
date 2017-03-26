// PictureProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MenuUi.h"

#define yAxis 6 //amount of commands in y axis
int main()
{
	MenuUi ui(yAxis);
	ui.start();
    return 0;
}

