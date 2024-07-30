#include <iostream>
using namespace std;

class Time
{
    protected:
        int hours;
        int minutes;

    public:
        Time() { hours = 0, minutes = 0; };
        Time(int h, int m):hours(h), minutes(m) { };
        void showTime() const
        {
            cout << hours << " Hours " << minutes << " Minutes " << endl;
        }
        Time operator++(int);
};

Time Time::operator++(int)
{
    int m;
    Time time(this->hours, this->minutes);
    m = hours * 60 + (++minutes);
    hours = m / 60;
    minutes = m % 60;
    return time;
}

int main()
{
    Time t1(2, 25), t3, t4;

    cout << "t1 : " ;
    t1.showTime();

    t3 = t1++ ; // t3 = t1.operator++(0);
    cout << endl << "(t3 = t1++) ==> " << endl;

    cout << "t1 : " ;
    t1.showTime();

    cout << "t3 : " ;
    t3.showTime();

    return 0;
}
