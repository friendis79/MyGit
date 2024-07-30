#include <iostream>
using namespace std;

int main()
{
    int a[3] = {10, 20, 30};
    int i;

    for (i=0; i<3; i++) 
        cout << i << " 번째 원소의 주소: " << (a+i) << endl;
    cout << endl;

    for (i=0; i<3; i++)
        cout << i << " 번째 원소의 주소: " << &a[i] << endl;
    cout << endl;

    for (i=0; i<3; i++) 
        cout << i << " 번째 원소의 값: " << a[i] << endl;
    cout << endl;

    for (i=0; i<3; i++)
        cout << i << " 번째 원소의 값: " << *(a+i) << endl;
    cout << endl;

    return 0;
}