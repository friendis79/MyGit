#include <iostream>
using namespace std;

class Time
{
    protected:
        int hours;
        int minutes;

    public :
        Time(int h, int m) : hours(h), minutes(m) {};
        void showTime() const
        {
            cout << hours << " Hours " << minutes << " Minutes " << endl;
        }
        Time operator+(const Time & t) const;
        Time operator-(const Time & t) const;
};

Time Time::operator+(const Time & t) const
{
    Time tsum(0, 0);
    int m1, m2;

    m1 = hours*60 + minutes;
    m2 = t.hours*60 + t.minutes;
    tsum.hours = (m1 + m2) / 60;
    tsum.minutes = (m1 + m2) % 60;
    return tsum;
}

Time Time::operator-(const Time &t) const
{
    Time tm(0, 0);
    int m1, m2;

    m1 = hours*60 - minutes;
    m2 = t.hours*60 - t.minutes;
    if (m1 > m2)
    {
        tm.hours = (m1 - m2) / 60;
        tm.minutes = (m1 - m2) % 60;
    }
    else
    {
         cout << "Unavailable" << endl;
         exit;
    }

    return tm;
}

int main()
{
    Time t1(2, 25), t2(3, 45), ts(0, 0);
    cout << "t1 => ";
    t1.showTime();
    cout << "t2 => ";
    t2.showTime();

    cout << "t1.operator+(t2) => ";
    ts = t1.operator+(t2);
    ts.showTime();
    cout << "t1 + t2 => ";
    ts = t1 + t2;
    ts.showTime();
    
    cout << endl;

    Time t3(5, 10), t4(1, 35), tm(0, 0);
    cout << "t3 => ";
    t3.showTime();
    cout << "t4 => ";
    t4.showTime();

    cout << "t3.operator-(t4) => ";
    tm = t3.operator-(t4);
    tm.showTime();
    cout << "t3 - t4 => ";
    tm = t3 - t4;
    tm.showTime();

    return 0;
}