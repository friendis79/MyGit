#include <iostream>
using namespace std;

int main()
{
    int ia = 100;
    int ib = 200;

    const int* p1 = &ia; // p1은 const int 형을 가리키는 포인터이다. 
    cout << "*p1 = " << *p1 << endl;

    p1 = &ib; // p1은 변경할 수 있다. 
    cout << "p1 = " << p1 << endl;

    // *p1 = 300; // 오류: p1이 가리키는 변수의 값은 변경할 수 없다.

    int* const p2 = &ia;  // int 형을 가리키는 p2는 const로 제한된다. 
    cout << "p2 = " << p2 << endl;

    // p2 = &ib; // 오류: p2는 변경할 수 없다. 

    *p2 = 300; // p2가 가리키는 변수의 값은 변경할 수 있다. 
    cout << "*p2 = " << *p2 << endl;

    const int* const p3 = &ia; // 포인터 p3과 p3이 가리키는 변수 모두 const로 제한된다. 
    cout << "p3 = " << p3 << endl;

    // p3 = &ib; // 오류: p3은 변경할 수 없다. 
    // *p3 = 300; // 오류: p3이 가리키는 변수의 값은 변경할 수 없다.

    return 0;
}