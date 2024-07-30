#include <iostream>
using namespace std;

typedef unsigned char BYTE;
typedef struct complex {
    double real;
    double image;
} COMPLEX;

int main()
{
    COMPLEX comp1 = {10.5, 8.2};
    cout << "comp1의 실수부 : " << comp1.real << endl;
    cout << "comp1의 허수부 : " << comp1.image << endl;

    BYTE a = 'A', b = '0';
    cout << "a = " << a << ", b = " << b << endl;

    return 0;
}