#include <iostream>
using namespace std;

int Add(int x, int y = 1); // 함수의 원형 선언

int main()
{
    int sum;
    cout << "인수가 10, 20 으로 전달한 경우" << endl;
    sum = Add(10, 20);

    cout << "sum = " << sum << endl << endl;
    cout << "인수가 10 으로 전달한 경우" << endl;
    sum = Add(10);
    
    cout << "sum = " << sum << endl << endl;

    return 0;
}

int Add(int x, int y) // 함수의 정의
{
    cout << "x = " << x << ", y = " << y << endl;
    return (x + y);
}   