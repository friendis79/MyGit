#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char flower[20]; // ���ڿ��� ������ �迭
    char *ptr; // ���ڿ��� ����Ű�� ������

    // ���ڿ� "freesia"�� flower �迭�� ����
    strcpy(flower, "freesia");
    cout << "1. flower : " << flower << endl; // ���: 1. flower : freesia
    ptr = flower; // ptr �����Ϳ� flower �迭�� �ּҸ� �Ҵ�
    cout << "2. ptr : " << ptr << endl << endl; // ���: 2. ptr : freesia

    // ���ڿ� "rose"�� ptr�� ����Ű�� ��ġ�� ����
    strcpy(ptr, "rose");
    cout << "3. ptr : " << ptr << endl << endl; // ���: 3. ptr : rose

    // ���ڿ� "mary"�� flower �迭�� �̾ ����
    strcat(flower, "mary");
    cout << "4. flower : " << flower << endl; // ���: 4. flower : rosemary
    ptr = flower; // ptr �����Ϳ� flower �迭�� �ּҸ� �Ҵ�
    strcat(ptr, " perfume"); // ptr�� ����Ű�� ��ġ�� " perfume"�� �̾ ����
    cout << "5. ptr : " << ptr << endl; // ���: 5. ptr : rosemary perfume
    cout << "ptr ���ڿ��� ���̴� " << strlen(ptr) << endl << endl; // ���: ptr ���ڿ��� ���̴� 18
    
    return 0;
}
