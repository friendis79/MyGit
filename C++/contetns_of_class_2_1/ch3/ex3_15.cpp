#include <iostream>
using namespace std;
const double PI = 3.14159;

int main()
{
    int num=0;
    double a, b, area;
    do {
        cout << "==================================" << endl ;
        cout << " 1. �ﰢ���� ���̱��ϱ� " << endl ;
        cout << " 2. �簢���� ���̱��ϱ� " << endl ;
        cout << " 3. ���� ���̱��ϱ� " << endl ;
        cout << " 9. ������ " << endl ;
        cout << "==================================" << endl ;
        cout << "���ϴ� ������ �����ϼ���: " ; 
        cin >> num;
        switch (num) {
        case 1: 
        case 2:
            cout << "�ظ��� ���̸� �Է��ϼ���: " ;
            cin >> a;
            cout << "���̸� �Է��ϼ���: " ;
            cin >> b ;
        break ;

        case 3:
            cout << "�������� �Է��ϼ���: " ;
            cin >> a;
        break ;

        case 9:
            cout << "�����մϴ�." << endl ;
        return 0 ;

        default:
        cout << "�Է��� �߸��Ͽ����ϴ�! " << endl << endl ;
        continue;
    }
    switch (num) {
        case 1: 
            area = a * b / 2;
        break ;

        case 2:
            area = a * b;
        break ;

        case 3:
            area = PI * a * a;
        }
    cout << "area = " << area << endl << endl;
    } while (num != 9);

    return 0;
}