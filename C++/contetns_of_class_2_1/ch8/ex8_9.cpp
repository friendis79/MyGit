#include <iostream>
using namespace std;

class Time
{
    private:
        int hour;
        int minute;

    public:
        Time():hour(0), minute(0) {};
        Time(int h, int m):hour(h), minute(m) {};
        void showTime() const
        {
            cout << hour << "시간" << minute << "분" << endl;
        }
        friend istream& operator>>(istream& stream, Time& t);
        friend ostream& operator<<(ostream& stream, const Time& t);
};

istream& operator>>(istream& stream, Time& t)
{
    stream >> t.hour >> t.minute;
    return stream;
}

ostream& operator<<(ostream& stream, const Time& t)
{
    stream << "(" << t.hour << ", " << t.minute << ")";
    return stream;
}

int main()
{
    Time t1, t2, t3;
    cout << "t1을 입력하세요: " ;
    cin >> t1;
    cout << "t2을 입력하세요: " ;
    cin >> t2;
    cout << "t3을 입력하세요: " ;
    cin >> t3;
    cout << endl;
    cout << "t1: " << t1 << ", t2: " << t2 << ", t3: " << t3 << endl;
}
