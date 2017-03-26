/* Header file of Counter Class*/
#include <iostream>
using namespace std;
//Class definition
class Counter {
    friend ostream &operator<<(ostream &out, const Counter &c);
    public:
        Counter(int n0 = 0);
		operator const int();
        Counter &operator++();
        Counter operator++(int);
		Counter &operator--();
		Counter operator--(int);
        bool operator<(const Counter &c2) const;
        void reset();
		int getCount() const;
    private:
        int count;
};

