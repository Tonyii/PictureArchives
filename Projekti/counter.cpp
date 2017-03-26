/* Implementation of Counter Class*/
#include "stdafx.h"
#include "counter.h"
#include <iostream>

//Implementation of class Counter
Counter:: Counter(int n0) {
     count = n0;
}
Counter::operator const int()
{
	return count;
}
Counter& Counter::operator++() {
   count++;
   return *this;
}
Counter Counter::operator++(int) {
   Counter old = *this;;
   count++;
   return old;
}
Counter & Counter::operator--()
{
	count--;
	return *this;
}
Counter Counter::operator--(int)
{
	Counter old = *this;;
	count--;
	return old;
}
void Counter::reset(){
   count = 0;
}
int Counter::getCount() const{
   return count;
}

bool Counter::operator<(const Counter &c2) const {
 	return count < c2.count;
}
ostream &operator<<(ostream & out, const Counter &c) {
     out << c.count ;
     return out;
}
