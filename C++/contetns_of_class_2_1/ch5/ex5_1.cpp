#include <iostream>
using namespace std;

int add(int, int); // 함수의 원형 선언
void multiply(int, int); // 함수의 정의가 호출 뒤에 있으므로 선언이 필요

int main()
{ 
    int a = 15, b = 10, sum;

    sum = add(a, b); // 함수의 호출 - a, b는 실인수
    cout << a << " + " << b << " = " << sum << endl;

    multiply(a, b); // 함수의 호출 - a, b는 실인수
    return 0;
}

int add(int x, int y) // 함수의 정의 - x, y는 가인수
{
int sum;
sum = x + y;
return sum;
}

void multiply(int x, int y) // 함수의 정의 - x, y는 가인수
{
cout << x << " * " << y << " = " << x * y << endl;
}