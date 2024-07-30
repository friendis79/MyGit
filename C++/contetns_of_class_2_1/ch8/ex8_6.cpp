#include <iostream>
using namespace std;

class Time
{
    protected:
        int hours;
        int minutes;

    public:
        Time(int h, int m):hours(h), minutes(m) { };
        void showTime() const
        {
            cout << hours << " Hours " << minutes << " Minutes " << endl;
        }
        friend Time operator+(const Time& t1, const Time& t2);
};

Time operator+(const Time& t1, const Time& t2)
{
    Time tsum(0, 0);
    int m1, m2;

    m1 = t1.hours * 60 + t1.minutes;
    m2 = t2.hours * 60 + t2.minutes;

    tsum.hours = (m1 + m2) / 60;
    tsum.minutes = (m1 + m2) % 60;
    return tsum;
}

int main()
{
    Time t1(2, 25), t2(3, 45), ts(0,0);

    cout << "t1 => " ;
    t1.showTime() ;

    cout << "t2 => " ;
    t2.showTime() ;

    cout << "operator+(t1, t2) => " ;
    ts = operator+(t1, t2) ; // ts = t1 + t2;
    ts.showTime() ;
    
    cout << "t1 + t2 => " ;
    ts = t1 + t2 ;
    ts.showTime();
}
