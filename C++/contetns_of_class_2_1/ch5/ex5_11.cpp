#include <iostream>
using namespace std;

int Add(int x, int y);
int Add(int *x, int *y);
double Add(double x, double y);
double Add(double* x, double* y);

int main()
{
    int a = 8, b = 24, c;
    double r = 20.5, s = 12.8, t;

    c = Add(a, b);
    cout << a << " + " << b << " = " << c << endl;

    c = Add(&a, &b);
    cout << a << " + " << b << " = " << c << endl;

    t = Add(r, s);
    cout << r << " + " << s << " = " << t << endl;
    
    t = Add(&r, &s);
    cout << r << " + " << s << " = " << t << endl;

    return 0;
}

int Add(int x, int y)
{
    cout << "int Add(int x, int y) 호출 ==> " ;
    return (x + y);
}

int Add(int *x, int *y)
{
    cout << "int Add(int *x, int *y) 호출 ==> " ;
    return (*x + *y);
}

double Add(double x, double y)
{
    cout << "double Add(double x, double y) 호출 ==> " ;
    return (x + y);
}

double Add(double* x, double* y)
{
    cout << "double Add(double* x, double* y) 호출 ==> " ;
    return (*x + *y);
}