#include <iostream>
using namespace std;

#define PI 7 // 매크로 상수 선언
const double pi = 3.14159; // const 상수 선언

int main()
{
    int r = 10;
    double s;
    
    s = pi * r * r;
    cout << "(const 상수 사용) area = " << s << endl;
    s = PI * r * r;
    cout << "(매크로 상수 사용) area = " << s << endl;

    return 0;
}