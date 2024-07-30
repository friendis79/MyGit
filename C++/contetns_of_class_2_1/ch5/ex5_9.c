#include <stdio.h>

int add(int x, int y);
double Add(double x, double y);
int intAdd(int x, int y);
double doubleAdd(double x, double y);

int main()
{
    int a = 8, b = 24, c;
    double e = 5.8, f = 28.7, g;

    c = intAdd(a, b);
    printf("%d + %d = %d \n", a, b, c);

    g = doubleAdd(e, f);
    printf("%f + %f = %f \n", e, f, g);

    return 0;
}

int add(int x, int y)
{
    printf("int Add(int x, int y) 호출==> " );
    return (x + y);
}

double Add(double x, double y)
{
    printf("double Add(double x, double y) 호출==> " );
    return (x + y);
}

int intAdd(int x, int y)
{
    return (x + y);
}

double doubleAdd(double x, double y)
{
    return (x + y);
}