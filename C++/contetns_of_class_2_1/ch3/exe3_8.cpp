#include <iostream>
using namespace std;

int main()
{
    int a, b, max;

    cout << "a�� b ���� �Է��Ͻÿ�: ";
    cin >> a >> b;

    a >= b ? max = a : max = b;
    cout << "ū ���� " << max << "�Դϴ�." << endl;

    return 0;
}