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
    cout << "comp1�� �Ǽ��� : " << comp1.real << endl;
    cout << "comp1�� ����� : " << comp1.image << endl;

    BYTE a = 'A', b = '0';
    cout << "a = " << a << ", b = " << b << endl;

    return 0;
}