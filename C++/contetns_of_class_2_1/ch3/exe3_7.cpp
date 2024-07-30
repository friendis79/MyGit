#include <iostream>
using namespace std;

int main() 
{
    float f1, f2, f3;
    int n1;

    f1 = 5 / 2;
    f2 = 5.0f / 2;
    f3 = 5 / 2.0f;
    n1 = 5.0f / 2.0f;

    cout << "5 / 2 = " << f1 << endl;
    cout << "5.0 / 2 = " << f2 << endl;
    cout << "5 / 2.0 = " << f2 << endl;
    cout << "5.0 / 2.0 = " << n1 << endl; 

    return 0;
}