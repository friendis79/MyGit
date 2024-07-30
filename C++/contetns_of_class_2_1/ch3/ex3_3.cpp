#include <iostream>
using namespace std;

int main()
{
    int a = 3, b = -5, c = 0;
    bool x;

    x = a && b;
    cout << "x = a && b --> x = " << x << endl;

    x = a && c;
    cout << "x = a && c --> x = " << x << endl;

    x = a || b;
    cout << "x = a || b --> x = " << x << endl;

    x = !c;
    cout << "x = !c --> x = " << x << endl;

    return 0;
}