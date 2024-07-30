#include <iostream>
using namespace std;

class Time
{
    protected:
        int hours;
        int minutes;

    public:
        Time() { hours = 0, minutes = 0; };
        Time(int h, int m):hours(h), minutes(m) {};
        void showTime() const
        {
            cout << hours << " Hours " << minutes << " Minutes " << endl;
        }
        Time& operator++();
};

Time& Time::operator++()
{
    int m;
    m = hours * 60 + (++minutes);
    hours = m / 60;
    minutes = m % 60;

    return (*this);
}

int main()
{
    Time t1(2, 25), t2, t3; 

    cout << "t1 : " ;
    t1.showTime();

    t2 = ++t1 ; // t2 = t1.operator++() ;
    cout << endl << "(t2 = ++t1) ==> " << endl;

    cout << "t1 : " ;
    t1.showTime();

    cout << "t2 : " ;
    t2.showTime();

    return 0;
}
