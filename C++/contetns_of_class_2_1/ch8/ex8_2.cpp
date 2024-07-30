#include <iostream>
using namespace std;

class Time
{
    protected:
        int hour;
        int minute;

    public:
        Time(int h, int m):hour(h), minute(m) { };
        void showTime() const
        {
            cout << hour << " 시간" << minute << "분" << endl;
        }
        bool operator==(const Time& t) const;
};

bool Time::operator==(const Time& t) const
{
    int m1, m2;
    m1 = hour * 60 + minute;
    m2 = t.hour * 60 + t.minute;

    return (m1 == m2);
}
int main()
{
    Time t1(2, 25), t2(1, 85);
    bool d = (t1 == t2) ; // d = (t1.operator==(t2)) ;

    cout << "t1 : ";
    t1.showTime();

    cout << "t2 : ";
    t2.showTime();
    cout << "(t1 == t2) ==> " << d;
    if (t1 == t2)    cout << " : t1과 t2는 같다." << endl;
    else             cout << " : t1과 t2는 같지 않다." << endl;

    return 0;
}
