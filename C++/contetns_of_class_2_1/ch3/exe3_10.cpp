#include <iostream>
using namespace std;

int main()
{
    int inum = 100;
    int* iptr;
    double fnum = 12.5;
    double *fptr;

    iptr = &inum;
    printf("inum�� �ּ�= %p\n", &inum);
    printf("iptr�� ����Ű�� �������� ��= %d\n", *iptr);
    fptr = &fnum;
    cout << "fnum�� �ּ�= " << &fnum << endl;
    cout << "fptr�� ����Ű�� �������� ��= " << *fptr << endl;

    return 0;
}