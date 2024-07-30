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
        friend Time operator*(Time t, int a);
        friend Time operator*(int a, Time t); // 멤버 함수로는 구현할 수 없다.
};

Time operator*(Time x, int a)
{
    Time t(0, 0);
    int m;
    m = x.hours * a * 60 + x.minutes * a;
    t.hours = m / 60;
    t.minutes = m % 60;

    return t;
}

Time operator*(int a, Time x)
{
    Time t(0, 0);
    int m;
    m = x.hours * a * 60 + x.minutes * a;
    t.hours = m / 60;
    t.minutes = m % 60;
    return t;
}

int main()
{
    Time tx(2, 25), tz(0,0);

    cout << "tx = " ;
    tx.showTime();

    cout << "tx * 3 = " ;
    tz = tx * 3;
    tz.showTime();
    
    cout << "3 * tx = " ;
    tz = 3 * tx;
    tz.showTime();
}