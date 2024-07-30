#include <iostream>
using namespace std;

struct student {
    int id;
    char name[20];
};

int main()
{
    student stu1 = {1234, "Hong Gildong"};
    student stu2;

    cin >> stu2.id;
    cin >> stu2.name;
    
    student *pstu = new student;
    cin >> pstu->id;
    cin >> pstu->name;

    cout << "stu1.id : " << stu1.id << ", stu1.name : " << stu1.name << endl;
    cout << "su2.id : " << stu2.id << ", stu2.name : " << stu2.name << endl;
    cout << "(*pstu).id : " << (*pstu).id << ", (*pstu).name : " << (*pstu).name << endl;
    cout << "pstu->id : " << pstu->id << ", pstu->name : " << pstu->name << endl;
    
    delete pstu;

    return 0;
}