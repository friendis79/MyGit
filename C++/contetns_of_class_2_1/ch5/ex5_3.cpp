#include <iostream>
using namespace std;

int add(int, int);

int main()
{
    int a = 20, b = 30, sum;
    sum = add(a, b); // a와 b의 값 20과 30이 전달된다. 
    // add() 함수에서 반환된 값이 sum에 대입된다. 
    cout << a << " + " << b << " = " << sum << endl;

    return 0;
}

int add(int x, int y) // 20과 30이 x와 y에 복사된다. 
{
    int z;
    z = x + y;

    return z; // z의 값을 반환한다. 
}