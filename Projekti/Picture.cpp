#include "stdafx.h"
#include "Picture.h"
#include <iomanip>

int Picture::pictureCount = 0;

Picture::Picture()
{
}

Picture::Picture(string filename_,string description_, string location_, int nrOfPeople_) : filename(filename_), description(description_), location(location_), nrOfPeople(nrOfPeople_)
{
	++pictureCount;
}

Picture::Picture(const Picture & c)
{
	filename = c.filename;
	description = c.description;
	location = c.location;
	nrOfPeople = c.nrOfPeople;
	++pictureCount;
}

int Picture::getPeople()
{
	return nrOfPeople;
}


int Picture::getCount()
{
	return pictureCount;
}

const Picture & Picture::operator=(const string & pointy)
{
	cursor = pointy;
	return *this;
}

Picture::~Picture()	
{
	--pictureCount;
}

ostream & operator<<(ostream &out, const Picture &o) {
	out << left << setw(3) << o.cursor << setw(20) << o.filename << setw(20) << o.location << setw(3) << o.nrOfPeople << "\n   " << o.description;
	return out;
}




