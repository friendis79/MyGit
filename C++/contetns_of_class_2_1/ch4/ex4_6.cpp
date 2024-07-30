#include <iostream>
using namespace std;

int main()
{
    int num = 100;
    int *pnum, **ppnum;

    pnum = &num;
    ppnum = &pnum;

    cout << "num : " << num << endl;
    cout << "*pnum : " << *pnum << endl;
    cout << "**ppnum : " << **ppnum << endl << endl;
    cout << "ppnum : " << ppnum << endl;
    cout << "pnum?? 주소 " << &pnum << endl;
    cout << "pnum : " << pnum << endl;
    cout << "num?? 주소 " << &num << endl;

    return 0;
}