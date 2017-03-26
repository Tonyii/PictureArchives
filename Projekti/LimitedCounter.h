#pragma once
#define _ALLOW_MSC_VER_MISMATCH
#include "counter.h"

class LimitedCounter: public Counter
{
	
public:
	LimitedCounter(int initial_, int max_);
	~LimitedCounter();
	LimitedCounter &operator++();
	LimitedCounter operator++(int);
	LimitedCounter &operator--();
	LimitedCounter operator--(int);
	void setLimit(int limit);
private:
	int maxLimit;
};

