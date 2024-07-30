#include <iostream>
using namespace std;

int main()
{
    int *id; // 포인터 선언
    id = new int; // 기억공간 할당

    cout << "번호를 입력하세요: " ; 
    cin >> *id;

    char *name = new char[20] ; // 포인터 선언과 기억공간 할당

    cout << "이름을 입력하세요: " ; 
    cin >> *name;
    cout << "id : " << *id << ", name : " << name << endl;

    delete id; // 기억공간 해제
    delete [] name; // 배열 기억공간 해제

    return 0;
}