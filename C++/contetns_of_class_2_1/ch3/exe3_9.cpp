#include <iostream>
using namespace std;

int main()
{
    int c; // �޸� ������ ���
    float t, f;

    cout << "���� �µ��� �Է��Ͻÿ�: ";
    cin >> c;
    f = (t = c * 9.0f/5.0f, t += 32); // �޸� ������ ���
    cout << "ȭ�� �µ��� " << f << "���Դϴ�." <<endl;

    return 0;
}