#include <iostream>
using namespace std;

int main()
{
    int *id; // ������ ����
    id = new int; // ������ �Ҵ�

    cout << "��ȣ�� �Է��ϼ���: " ; 
    cin >> *id;

    char *name = new char[20] ; // ������ ����� ������ �Ҵ�

    cout << "�̸��� �Է��ϼ���: " ; 
    cin >> *name;
    cout << "id : " << *id << ", name : " << name << endl;

    delete id; // ������ ����
    delete [] name; // �迭 ������ ����

    return 0;
}