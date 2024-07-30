#include <iostream>
using namespace std;

int x;

int &Set_x()
{
    return x;
}

int main()
{
    cout << "x = " << x << endl;
    Set_x() = 1000;
    cout << "x = " << Set_x << endl;

    return 0;
}