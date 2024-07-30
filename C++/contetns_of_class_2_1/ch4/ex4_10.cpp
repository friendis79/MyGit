#include <iostream>
using namespace std;

struct Student 
{
    int id;
    char name[20];
};

int main()
{
    Student *pst;
    pst = new Student; // 기억공간을 동적으로 할당 

    cout << "번호를 입력하세요: " ; 
    cin >> pst->id;

    cout << "이름을 입력하세요: " ; 
    cin >> pst->name;

    cout << "번호 : " << pst->id << ", 이름 : " << pst->name << endl;
    delete pst; // 기억공간 해제

    return 0;
}