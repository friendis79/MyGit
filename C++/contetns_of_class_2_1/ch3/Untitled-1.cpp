#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char grade;
    char* lv;

    cout << "ют╥б : ";
    cin >> grade;

    switch (grade)
    {
    case 'a':
        lv = strcpy(lv, "Good Customer");
        break;
    case 'b':
        lv = strcpy(lv, "Normal Customer");
        break;
    default:
        break;
    }

    cout << lv << endl;
}