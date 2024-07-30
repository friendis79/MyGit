#include <iostream>
using namespace std;

int Add(int x, int y)
{
    cout << "int Add(int x, int y) 호출==> ";
    return (x + y);
}

double Add(double x, double y)
{
    cout << "double Add(double x, double y) 호출==> ";
    return (x + y);
}

int main()
{
    int a = 8, b = 24, c;
    double e = 5.8, f = 28.7, g;
    c = Add(a, b);
    cout << a << " + " << b << " = " << c << endl;
    g = Add(e, f);
    cout << e << " + " << f << " = " << g << endl;

    return 0;
}