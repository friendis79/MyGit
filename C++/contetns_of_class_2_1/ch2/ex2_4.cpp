#include <iostream>
#include <string>
using namespace std;

int main()
{
    string ss1 = "Good-";
    string ss2 = "afternoon.";
    string ss3;

    cout << "ss1 : " << ss1 << endl;
    cout << "ss2 : " << ss2 << endl;
    ss3 = ss1;
    cout << "ss3 = ss1 : " << ss3 << endl;
    ss3 += ss2;
    cout << "ss3 += ss2 : " << ss3 << endl;
}