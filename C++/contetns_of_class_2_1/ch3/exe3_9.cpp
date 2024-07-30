#include <iostream>
using namespace std;

int main()
{
    int c; // 콤마 연산자 사용
    float t, f;

    cout << "섭씨 온도를 입력하시오: ";
    cin >> c;
    f = (t = c * 9.0f/5.0f, t += 32); // 콤마 연산자 사용
    cout << "화씨 온도는 " << f << "도입니다." <<endl;

    return 0;
}