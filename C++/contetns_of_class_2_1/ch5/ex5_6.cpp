#include <iostream>
using namespace std;

#define PI 7 // ��ũ�� ��� ����
const double pi = 3.14159; // const ��� ����

int main()
{
    int r = 10;
    double s;
    
    s = pi * r * r;
    cout << "(const ��� ���) area = " << s << endl;
    s = PI * r * r;
    cout << "(��ũ�� ��� ���) area = " << s << endl;

    return 0;
}