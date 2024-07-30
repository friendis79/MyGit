#include <iostream>
using namespace std;

struct Student {
    int id;
    char name[16];
    float score;
};

union Register{
    char ch;
    short sh;
    long lo;
};

int main()
{
    Student stu1 = {123456, "ȫ�浿", 91.5};
    Register reg1;
    reg1.lo = 0x12345678;

    cout << "size of stu1 : " << sizeof(stu1) << endl;
    cout << "size of reg1 : " << sizeof(reg1) << endl << endl;

    printf("reg1.ch = %8x \n", reg1.ch);
    printf("reg1.sh = %8x \n", reg1.sh);
    printf("reg1.lo = %8x \n", reg1.lo);

    return 0;
}