#include "stdafx.h"
#include "LimitedCounter.h"


LimitedCounter::LimitedCounter(int initial_, int max_) : Counter(initial_), maxLimit(max_)
{
}


LimitedCounter::~LimitedCounter()
{
}

LimitedCounter & LimitedCounter::operator++()
{
	{
		if (Counter::getCount() < maxLimit) {
			Counter::operator++();
		}
		return *this;
	}
}

LimitedCounter LimitedCounter::operator++(int)
{
	LimitedCounter oldCounter = *this;
	if (Counter::getCount() < maxLimit) {
		Counter::operator++();
	}
	return oldCounter;
}

LimitedCounter & LimitedCounter::operator--()
{
	if (Counter::getCount() > 0) Counter::operator--();
	return *this;
}

LimitedCounter LimitedCounter::operator--(int)
{
	LimitedCounter oldCounter = *this;
	if (Counter::getCount() > 0) {
		Counter::operator--();
	}
	return oldCounter;
}

void LimitedCounter::setLimit(int limit)
{
	maxLimit = limit;
	if (Counter::getCount() > limit) {
		Counter::reset();
		for (int i = 0; i < limit; i++) {
			Counter::operator++();
		}
	}
}



