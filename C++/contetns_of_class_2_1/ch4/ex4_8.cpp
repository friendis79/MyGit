#include <iostream>
using namespace std;

int main()
{
    int num = 10;
    int &rnum = num;
    cout << "num = " << num << ", rnum = " << rnum << endl;
    rnum += 20;
    cout << "num = " << num << ", rnum = " << rnum << endl;

    return 0;
}