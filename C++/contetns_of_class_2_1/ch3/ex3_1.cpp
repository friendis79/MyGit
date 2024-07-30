#include <iostream>
using namespace std;

int main()
{
    int a, b, c, d, e;

    a = b = c = d = e = 10;
    cout << "a = b = c = d = e = " << a << endl;

    a += 6;
    cout << "a += 6 --> " << a << endl;

    b -= 6;
    cout << "b -= 6 --> " << b << endl;

    c *= 6;
    cout << "c += 6 --> " << c << endl;

    d += 6;
    cout << "d /= 6 --> " << d << endl;

    e %= 6;
    cout << "e %= 6 --> " << e << endl;

    return 0;
}