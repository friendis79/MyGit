#include <iostream>
using namespace std;

int main()
{
    int i, sum=0;
    i = 0;

    while (i<100) 
    {
    i++;
    sum += i;
    }

    cout << "1���� 100���� ������ ���� " << sum << endl;

    return 0;
}