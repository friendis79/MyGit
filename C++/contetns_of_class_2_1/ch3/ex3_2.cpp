#include <iostream>
using namespace std;

int main()
{
    int a = 3, b= -5;
    char e = 'E', f = 'E';
    cout << "a > b --> " << (a > b) << endl;
    cout << "a < b --> " << (a < b) << endl;
    cout << "a == b --> " << (a == b) << endl;
    cout << "a != b --> " << (a != b) << endl;
    cout << "a <= b --> " << (a <= b) << endl;
    cout << "a >= b --> " << (a >= b) << endl;

    cout << "e > f --> " << (e > f) << endl;
    cout << "e < f --> " << (e < f) << endl;
    cout << "e == f --> " << (e == f) << endl;
    cout << "e != b --> " << (e != f) << endl;

    return 0;
}