#include <iostream>
using namespace std;

int main()
{
    int a, b, max;

    cout << "a와 b 값을 입력하시오: ";
    cin >> a >> b;

    a >= b ? max = a : max = b;
    cout << "큰 수는 " << max << "입니다." << endl;

    return 0;
}