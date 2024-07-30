#include <iostream>
using namespace std;

class Time
{
    protected:
        int hour;
        int minute;

    public:
        Time(int h, int m):hour(h), minute(m) {};
        void showTime() const
        {
            cout << hour << "시간" << minute << "분" << endl;
        }
        friend ostream& operator<<(ostream& os, const Time& t);
};

ostream& operator<<(ostream& stream, const Time& t)
{
    stream << "(" << t.hour << ", " << t.minute << ") " ;
    return stream;
}

int main()
{
Time t1(2, 25), t2(1, 85), t3(3, 15);
cout << t1 << t2 << t3 << endl;
}
