#include <iostream>
using namespace std;

int main()
{
    int a[2][3] = {1, 2, 3, 4, 5, 6};
    int i, j;

    for (i=0; i<2; i++) 
    {
        for ( j=0; j<3; j++) 
        {
            cout << "&a[" << i << "][" << j << "] = " << &a[i][ j] << ", " ;
            cout << "a[" << i << "][" << j << "] = " << a[i][ j] << endl ;
        }
    }

    cout << endl;

    for (i=0; i<6; i++) 
    {
        cout << "a[0]+" << i << " = " << a[0]+i << ", " ;
        cout << "*(a[0]+" << i << ") = " << *(a[0]+i) << endl ;
    }

    cout << endl;

    return 0;
}