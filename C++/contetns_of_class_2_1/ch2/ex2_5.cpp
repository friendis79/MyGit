#include <iostream>
using namespace std;

struct Student {
    char* id;
    char name[10];
    float score;
};

int main()
{
    Student stu1;

    cout << "학번을 입력하시오 : \t";
    cin >> stu1.id;
    cout << "이름을 입력하시오 : \t";
    cin >> stu1.name;
    cout << "성적을 입력하시오 : \t";
    cin >> stu1.score;
    cout << endl;

    cout << "학번 : " << stu1.id << endl;
    cout << "이름 : " << stu1.name << endl;
    cout << "성적 : " << stu1.score << endl;

    return 0;
}