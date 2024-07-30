#include <iostream>
using namespace std;

int main()
{
    int i, sum=0;

    for (i=1; i<=100; i++)
        sum += i;

    cout << "1부터 100까지 정수의 합은 " << sum << endl;

    return 0;
}