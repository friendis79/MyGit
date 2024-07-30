#include <iostream>
using namespace std;

int main()
{
    int inum = 100;
    int* iptr;
    double fnum = 12.5;
    double *fptr;

    iptr = &inum;
    printf("inum의 주소= %p\n", &inum);
    printf("iptr이 가리키는 기억장소의 값= %d\n", *iptr);
    fptr = &fnum;
    cout << "fnum의 주소= " << &fnum << endl;
    cout << "fptr이 가리키는 기억장소의 값= " << *fptr << endl;

    return 0;
}